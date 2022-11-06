//
// Created by Joenhle on 2022/10/17.
//

#include <string>
#include <sstream>
#include <limits>
#include "execute_stage.h"
#include "map"
#include <numeric>
#include "sql/stmt/typecaster.h"
#include "util/util.h"
#include "sql/operator/join_operator.h"
#include "sql/operator/operator.h"

using namespace std;



RC ExecuteStage::do_select(SQLStageEvent *sql_event)
{
  auto select_stmt = (SelectStmt*)(sql_event->stmt());
  auto session_event = sql_event->session_event();
  auto tables = select_stmt->tables();
  auto table2index = unordered_map<string, int>();
  RC rc = SUCCESS;
  stringstream ss;
  vector<Operator*> operators;
  unordered_map<string, vector<FilterUnit*>> table_single_filters;
  unordered_map<string, vector<FilterUnit*>> cross_join_filters;
  vector<FilterUnit*> join_between_agg_filters;
  vector<FilterUnit*> other_filters;
  for (int i = 0; i < tables.size(); ++i) {
    auto table = tables[i];
    table_single_filters[table->name()] = vector<FilterUnit*>();
    cross_join_filters[table->name()] = vector<FilterUnit*>();
    table2index[table->name()] = i;
  }
  //分配filter_units
  for (auto filter_unit : select_stmt->filter_stmt()->filter_units()) {
    filter_unit->is_or = select_stmt->is_or;
    auto left_type = filter_unit->left()->type();
    auto right_type = filter_unit->right()->type();
    if (left_type == ExprType::VALUE && right_type == ExprType::VALUE) {
      table_single_filters[tables[0]->name()].push_back(filter_unit);
    } else if (left_type == ExprType::FIELD && right_type == ExprType::VALUE) {
      auto expr = (FieldExpr*)filter_unit->left();
      table_single_filters[expr->table_name()].push_back(filter_unit);
    } else if (left_type == ExprType::VALUE && right_type == ExprType::FIELD) {
      auto expr = (FieldExpr*)filter_unit->right();
      table_single_filters[expr->table_name()].push_back(filter_unit);
    } else if (left_type == ExprType::FIELD && right_type == ExprType::FIELD) {
      auto left = (FieldExpr*)filter_unit->left();
      auto right = (FieldExpr*)filter_unit->right();
      int compare = table2index[left->table_name()] - table2index[right->table_name()];
      if (compare == 0) {
        table_single_filters[left->table_name()].push_back(filter_unit);
      } else if (compare > 0) {
        cross_join_filters[left->table_name()].push_back(filter_unit);
      } else {
        cross_join_filters[right->table_name()].push_back(filter_unit);
      }
    } else {
      bool flag = false;
      auto has_agg = [](CalculateExpr* expr){
        auto agg_names = {"max", "MAX", "min", "MIN", "count", "COUNT", "sum", "SUM", "avg", "AVG"};
        for (auto cell : expr->expr_cells()) {
          for (auto agg_name : agg_names) {
            if (cell.find(string(agg_name)) != cell.npos) {
              return true;
            }
          }
        }
        return false;
      };
      if (left_type == ExprType::CALCULATE) {
        flag |= has_agg((CalculateExpr*)filter_unit->left());
      }
      if (!flag && right_type == ExprType::CALCULATE) {
        flag |= has_agg((CalculateExpr*)filter_unit->right());
      }
      if (!flag) {
        join_between_agg_filters.push_back(filter_unit);
      } else {
        other_filters.push_back(filter_unit);
      }
    }
  }
  //构造scan + 单表predicate
  for (auto table : tables) {
    Operator* scan_oper = try_to_create_index_scan_operator(table_single_filters[table->name()]);
    if (scan_oper == nullptr) {
      scan_oper = new TableScanOperator(table);
    }
    if (table_single_filters[table->name()].size() > 0) {
      Operator* predicate_oper = new PredicateOperator(table_single_filters[table->name()]);
      predicate_oper->add_child(scan_oper);
      operators.push_back(predicate_oper);
    } else {
      operators.push_back(scan_oper);
    }
  }
  // 构造left-deep-join树
  if (tables.size() > 1) {
    auto left = operators[0];
    for (int i = 1; i < tables.size(); ++i) {
      auto right = operators[i];
      Operator* join_oper = new JoinOperator(left, right);
      if (cross_join_filters[tables[i]->name()].size() > 0) {
        Operator* predicate_oper = new PredicateOperator(cross_join_filters[tables[i]->name()]);
        predicate_oper->add_child(join_oper);
        left = predicate_oper;
      } else {
        left = join_oper;
      }
    }
    operators.clear();
    operators.push_back(left);
  }

  auto rebuild = [&](Operator*& oper){
    oper->add_child(operators[0]);
    operators.clear();
    operators.push_back(oper);
  };

  //构造join between agg filters
  if (join_between_agg_filters.size() > 0) {
    Operator* predicate_oper = new PredicateOperator(join_between_agg_filters);
    rebuild(predicate_oper);
  }

  //构造aggregate
  if(select_stmt->aggregate_fields().size() != 0){
    vector<shared_ptr<TupleCellSpec>> gb_fields;
    for(auto gb_field : select_stmt->groupby_fields()){
      gb_fields.push_back(gb_field);
    }
    Operator* agg_oper = new AggregateOperator(select_stmt->aggregate_fields(), gb_fields);
    rebuild(agg_oper);
  }

  //构造剩余的predicate
  if (other_filters.size() > 0) {
    Operator* predicate_oper = new PredicateOperator(other_filters);
    rebuild(predicate_oper);
  }

  //构造orderby
  if (select_stmt->orderby_fields().size() > 0) {
    Operator* sort_oper = new SortOperator(select_stmt->orderby_fields());
    rebuild(sort_oper);
  }

  //构造project
  ProjectOperator* oper = new ProjectOperator(select_stmt->query_fields());
  oper->add_child(operators[0]);

  rc = oper->open();
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to open operator");
    return rc;
  }

  //子查询
  if (sql_event->is_sub_query()) {
    vector<VTuple*> sub_select_res;
    while ((rc = oper->next()) == SUCCESS) {
      Tuple* tuple = oper->current_tuple();
      if (nullptr == tuple) {
        rc = RC::INTERNAL;
        LOG_WARN("failed to get current record. rc=%s", strrc(rc));
        break;
      }
      VTuple *temp = new VTuple;
      switch (tuple->get_tuple_type()) {
        case TupleType::ROW:{
          temp->append_row_tuple(*(RowTuple*)(tuple));
          break;
        }
        case TupleType::V:{
          temp->merge(*tuple,*temp);
          break;
        }
        default:{
          LOG_WARN("UNKNOWN TUPLE_TYPE");
          break;
        }
      }
      sub_select_res.push_back(temp);
    }
    if (rc != RC::RECORD_EOF) {
      LOG_WARN("something wrong while iterate operator. rc=%s", strrc(rc));
      oper->close();
      return rc;
    }
    rc = oper->close();
    sql_event->set_sub_query_res(sub_select_res);
    return SUCCESS;
  }

  //正常查询
  print_tuple_header(ss, *oper,select_stmt->alias_map());
  while ((rc = oper->next()) == RC::SUCCESS) {
    Tuple * tuple = oper->current_tuple();
    if (nullptr == tuple) {
      rc = RC::INTERNAL;
      LOG_WARN("failed to get current record. rc=%s", strrc(rc));
      break;
    }
    tuple_to_string(ss, *tuple);
    ss << std::endl;
  }
  if (rc != RC::RECORD_EOF) {
    LOG_WARN("something wrong while iterate operator. rc=%s", strrc(rc));
    oper->close();
  } else {
    rc = oper->close();
  }
  session_event->set_response(ss.str());
  return RC::SUCCESS;

}


