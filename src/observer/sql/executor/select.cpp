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

using namespace std;

RC do_select_v2(SQLStageEvent *sql_event)
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
  vector<FilterUnit*> other_filters;
  for (int i = 0; i < tables.size(); ++i) {
    auto table = tables[i];
    table_single_filters[table->name()] = vector<FilterUnit*>();
    cross_join_filters[table->name()] = vector<FilterUnit*>();
    table2index[table->name()] = i;
  }
  //分配filter_units
  for (auto filter_unit : select_stmt->filter_stmt()->filter_units()) {
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
      other_filters.push_back(filter_unit);
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
  print_tuple_header(ss, *oper);
  while ((rc = oper->next()) == RC::SUCCESS) {
    Tuple * tuple = oper->current_tuple();
    if (nullptr == tuple) {
      rc = RC::INTERNAL;
      LOG_WARN("failed to get current record. rc=%s", strrc(rc));
      break;
    }
    tuple_to_string(ss, *tuple);
    cout << ss.str() << endl;
    ss << std::endl;
  }
  if (rc != RC::RECORD_EOF) {
    LOG_WARN("something wrong while iterate operator. rc=%s", strrc(rc));
    oper->close();
  } else {
    rc = oper->close();
  }
  session_event->set_response(ss.str());
}

RC ExecuteStage::do_select(SQLStageEvent *sql_event)
{
  return do_select_v2(sql_event);
//  SelectStmt *select_stmt = (SelectStmt *)(sql_event->stmt());
//  SessionEvent *session_event = sql_event->session_event();
//  RC rc = RC::SUCCESS;
//  stringstream ss;
//
//  if(select_stmt->tables().size()!=1){
//    std::unordered_map<std::string,Operator *> table2operator;
//  }else{
//    todo filter_unit的expr包含计算和聚合的时候直接不走索引，注意赛选
//    Operator *scan_oper = try_to_create_index_scan_operator(select_stmt->filter_stmt());
//    if (nullptr == scan_oper) {
//      scan_oper = new TableScanOperator(select_stmt->tables()[0]);
//    }
//
//    Operator *scan_oper = new TableScanOperator(select_stmt->tables()[0]);
//
//    DEFER([&] () {delete scan_oper;});
//    PredicateOperator pred_oper(select_stmt->filter_stmt()->filter_units());
//    pred_oper.add_child(scan_oper);
//
//    AggregateOperator *agg_oper = nullptr;
//    SortOperator *sort_oper = nullptr;
//    if(select_stmt->aggregate_fields().size()!=0 ){
//      vector<shared_ptr<TupleCellSpec>> gb_fields;
//      for(auto gb_field : select_stmt->groupby_fields()){
//        gb_fields.push_back(gb_field);
//      }
//      agg_oper = new AggregateOperator(select_stmt->aggregate_fields(),gb_fields);
//      agg_oper->add_child(&pred_oper);
//    }
//    if(select_stmt->orderby_fields().size()!=0){
//      sort_oper = new SortOperator(select_stmt->orderby_fields());
//      if(agg_oper != nullptr){
//        sort_oper->add_child(agg_oper);
//      }else{
//        sort_oper->add_child(&pred_oper);
//      }
//    }
//
//    ProjectOperator project_oper;
//    if(sort_oper == nullptr){
//      if(agg_oper == nullptr){
//        project_oper.add_child(&pred_oper);
//      }else{
//        project_oper.add_child(agg_oper);
//      }
//    }else{
//      project_oper.add_child(sort_oper);
//    }
//    //project_oper.add_child(&pred_oper);
//
//    for (auto tupleCell : select_stmt->query_fields()) {
//      project_oper.add_projection(tupleCell);
//    }
//    rc = project_oper.open();
//    if (rc != RC::SUCCESS) {
//      LOG_WARN("failed to open operator");
//      return rc;
//    }
//
//    print_tuple_header(ss, project_oper);
//    while ((rc = project_oper.next()) == RC::SUCCESS) {
//      // get current record
//      // write to response
//      Tuple * tuple = project_oper.current_tuple();
//      if (nullptr == tuple) {
//        rc = RC::INTERNAL;
//        LOG_WARN("failed to get current record. rc=%s", strrc(rc));
//        break;
//      }
//
//      tuple_to_string(ss, *tuple);
//      ss << std::endl;
//    }
//
//    if (rc != RC::RECORD_EOF) {
//      LOG_WARN("something wrong while iterate operator. rc=%s", strrc(rc));
//      project_oper.close();
//    } else {
//      rc = project_oper.close();
//    }
//  }
//  session_event->set_response(ss.str());
//  return rc;
}


