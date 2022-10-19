//
// Created by Joenhle on 2022/10/17.
//

#include <string>
#include <sstream>

#include "execute_stage.h"
#include "string"
#include "common/io/io.h"
#include "common/log/log.h"
#include "common/lang/defer.h"
#include "common/seda/timer_stage.h"
#include "common/lang/string.h"
#include "session/session.h"
#include "event/storage_event.h"
#include "event/sql_event.h"
#include "event/session_event.h"
#include "sql/expr/tuple.h"
#include "sql/operator/table_scan_operator.h"
#include "sql/operator/index_scan_operator.h"
#include "sql/operator/predicate_operator.h"
#include "sql/operator/delete_operator.h"
#include "sql/operator/project_operator.h"
#include "sql/stmt/stmt.h"
#include "sql/stmt/select_stmt.h"
#include "sql/stmt/update_stmt.h"
#include "sql/stmt/delete_stmt.h"
#include "sql/stmt/insert_stmt.h"
#include "sql/stmt/filter_stmt.h"
#include "storage/common/table.h"
#include "storage/common/field.h"
#include "storage/index/index.h"
#include "storage/default/default_handler.h"
#include "storage/common/condition_filter.h"
#include "storage/trx/trx.h"
#include "storage/clog/clog.h"
#include "map"
#include <numeric>

using namespace std;

bool check_cross_condition(vector<Tuple*> &merge_tuple, vector<FilterUnit*>& cross_filters, unordered_map<string, int>& table_index) {
  for (auto filter : cross_filters) {
    FieldExpr &left = *(FieldExpr *)filter->left();
    FieldExpr &right = *(FieldExpr *)filter->right();
    Tuple*& left_tuple = merge_tuple[table_index[string(left.table_name())]];
    Tuple*& right_tuple = merge_tuple[table_index[string(right.table_name())]];
    if (!filter->compare(left_tuple, right_tuple)) {
      return false;
    }
  }
  return true;
}

void dfs(stringstream& ss, vector<Operator*>& tuple_sets, unordered_map<string, int>& table_index, vector<vector<Field>>& projection_fields,
    vector<vector<FilterUnit*>> &single_filters, vector<FilterUnit*>& cross_filters, vector<Tuple*>& merge_tuple, int step) {
  int table_num = static_cast<int>(table_index.size());
  if (step == table_num) {
    if (check_cross_condition(merge_tuple, cross_filters, table_index)) {
      int projection_num = 0;
      for (auto projection : projection_fields) {
        projection_num += projection.size();
      }
      for (int i = 0; i < table_num; ++i) {
        Tuple *&tuple = merge_tuple[i];
        for (int j = 0; j < projection_fields[i].size(); ++j) {
          auto field = projection_fields[i][j];
          TupleCell tuple_cell;
          tuple->find_cell(field, tuple_cell);
          tuple_cell.to_string(ss);
          if (--projection_num == 0) {
            ss << "\n";
          } else {
            ss << " | ";
          }
        }
      }
    }
    return;
  }

  Operator *&current_operator = tuple_sets[step];
  current_operator->open();
  RC rc = RC::SUCCESS;
  while ((rc = current_operator->next()) == RC::SUCCESS) {
    Tuple *tuple = current_operator->current_tuple();
    bool flag = true;
    for (auto filter_unit : single_filters[step]) {
      if (!filter_unit->compare(tuple)) {
        flag = false;
        break;
      }
    }
    if (flag) {
      merge_tuple.push_back(tuple);
      dfs(ss, tuple_sets, table_index, projection_fields, single_filters, cross_filters, merge_tuple, step+1);
      merge_tuple.pop_back();
    }
  }
}

RC print_tuple_sets(stringstream& ss, vector<Operator*>& tuple_sets, SelectStmt& select_stmt) {
  const vector<Table*> &tables = select_stmt.tables();
  unordered_map<string, int> table_index;
  for (int i = 0; i < tables.size(); ++i) {
    table_index[string(tables[i]->name())] = i;
  }
  vector<vector<Field>> projections(tables.size());
  vector<vector<FilterUnit*>> single_filters(tables.size());
  vector<FilterUnit*> cross_filters;
  vector<FilterUnit*> both_value_filters;
  for (auto filter_unit : select_stmt.filter_stmt()->filter_units()) {
    Expression *left = filter_unit->left();
    Expression *right = filter_unit->right();
    FieldExpr* fieldExpr = nullptr;
    if (left->type() == ExprType::FIELD && right->type() == ExprType::FIELD) {
      cross_filters.push_back(filter_unit);
      continue;
    } else if (left->type() == ExprType::FIELD && right->type() == ExprType::VALUE) {
      fieldExpr = (FieldExpr *)left;
    } else if (left->type() == ExprType::VALUE && right->type() == ExprType::FIELD) {
      fieldExpr = (FieldExpr *)right;
    } else if (left->type() == ExprType::VALUE && right->type() == ExprType::VALUE) {
      both_value_filters.push_back(filter_unit);
      continue;
    }else {
      LOG_WARN("[print_tuple_sets] mismatch field type, both are value type");
      continue;
    }
    int index = table_index[string(fieldExpr->table_name())];
    single_filters[index].push_back(filter_unit);
  }
  
  for (int i = 0; i < select_stmt.query_fields().size(); ++i) {
    auto filed = select_stmt.query_fields()[i];
    int index = table_index[string(filed.table_name())];
    projections[index].push_back(filed);
    if (i == select_stmt.query_fields().size()-1) {
      ss << string(filed.table_name()) + "." << string(filed.field_name()) + "\n";
    } else {
      ss << string(filed.table_name()) + "." << string(filed.field_name()) + " | ";
    }
  }

  bool flag = true;
  for (auto value_filter : both_value_filters) {
    if (!value_filter->compare()) {
      flag = false;
      break;
    }
  }
  if (flag) {
    vector<Tuple*> merge_tuple;
    dfs(ss, tuple_sets, table_index, projections, single_filters, cross_filters, merge_tuple, 0);
  }
  return SUCCESS;
}

RC ExecuteStage::do_select(SQLStageEvent *sql_event)
{
  SelectStmt *select_stmt = (SelectStmt *)(sql_event->stmt());
  SessionEvent *session_event = sql_event->session_event();
  RC rc = RC::SUCCESS;
  if (select_stmt->tables().size() != 1) {
    int table_num = select_stmt->tables().size();
    vector<Operator*> tuple_list;
    for (int i = 0; i < table_num; ++i) {
      //todo(hjh) 先直接进行scan扫描，后面多列索引实现了再优化
      Operator* scan_oper = new TableScanOperator(select_stmt->tables()[i]);
      tuple_list.push_back(scan_oper);
    }
    stringstream ss;
    print_tuple_sets(ss, tuple_list, *select_stmt);
    for (auto oper : tuple_list) {
      oper->close();
      delete oper;
    }
    session_event->set_response(ss.str());
    return rc;
  }

  Operator *scan_oper = try_to_create_index_scan_operator(select_stmt->filter_stmt());
  if (nullptr == scan_oper) {
    scan_oper = new TableScanOperator(select_stmt->tables()[0]);
  }

  DEFER([&] () {delete scan_oper;});

  PredicateOperator pred_oper(select_stmt->filter_stmt());
  pred_oper.add_child(scan_oper);
  ProjectOperator project_oper;
  project_oper.add_child(&pred_oper);
  for (const Field &field : select_stmt->query_fields()) {
    project_oper.add_projection(field.table(), field.meta());
  }
  rc = project_oper.open();
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to open operator");
    return rc;
  }

  std::stringstream ss;
  print_tuple_header(ss, project_oper);
  while ((rc = project_oper.next()) == RC::SUCCESS) {
    // get current record
    // write to response
    Tuple * tuple = project_oper.current_tuple();
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
    project_oper.close();
  } else {
    rc = project_oper.close();
  }
  session_event->set_response(ss.str());
  return rc;
}


