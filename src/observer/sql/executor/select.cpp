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

using namespace std;

RC ExecuteStage::do_select(SQLStageEvent *sql_event)
{
  SelectStmt *select_stmt = (SelectStmt *)(sql_event->stmt());
  SessionEvent *session_event = sql_event->session_event();
  RC rc = RC::SUCCESS;
  stringstream ss;

  if(select_stmt->tables().size()!=1){
    std::unordered_map<std::string,Operator *> table2operator;
  }else{
//    todo filter_unit的expr包含计算和聚合的时候直接不走索引，注意赛选
//    Operator *scan_oper = try_to_create_index_scan_operator(select_stmt->filter_stmt());
//    if (nullptr == scan_oper) {
//      scan_oper = new TableScanOperator(select_stmt->tables()[0]);
//    }

    Operator *scan_oper = new TableScanOperator(select_stmt->tables()[0]);

    DEFER([&] () {delete scan_oper;});
    PredicateOperator pred_oper(select_stmt->filter_stmt()->filter_units());
    pred_oper.add_child(scan_oper);

    AggregateOperator *agg_oper = nullptr;
    SortOperator *sort_oper = nullptr;
    if(select_stmt->aggregate_fields().size()!=0 ){
      vector<TupleCellSpec> gb_fields;
      for(auto gb_field : select_stmt->groupby_fields()){
        gb_fields.push_back(*gb_field);
      }
      agg_oper = new AggregateOperator(select_stmt->aggregate_fields(),gb_fields);
      agg_oper->add_child(&pred_oper);
    }
    if(select_stmt->orderby_fields().size()!=0){
      sort_oper = new SortOperator(select_stmt->orderby_fields());
      if(agg_oper != nullptr){
        sort_oper->add_child(agg_oper);
      }else{
        sort_oper->add_child(&pred_oper);
      }
    }

    ProjectOperator project_oper;
    if(sort_oper == nullptr){
      if(agg_oper == nullptr){
        project_oper.add_child(&pred_oper);
      }else{
        project_oper.add_child(sort_oper);
      }
    }else{
      project_oper.add_child(sort_oper);
    }
    //project_oper.add_child(&pred_oper);

    for (auto tupleCell : select_stmt->query_fields()) {
      project_oper.add_projection(tupleCell);
    }
    rc = project_oper.open();
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to open operator");
      return rc;
    }

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
  }
  session_event->set_response(ss.str());
  return rc;
}


