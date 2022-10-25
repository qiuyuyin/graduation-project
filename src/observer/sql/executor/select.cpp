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

  Operator *scan_oper = try_to_create_index_scan_operator(select_stmt->filter_stmt());
  if (nullptr == scan_oper) {
    scan_oper = new TableScanOperator(select_stmt->tables()[0]);
  }

  DEFER([&] () {delete scan_oper;});
  PredicateOperator pred_oper(select_stmt->filter_stmt()->filter_units());
  pred_oper.add_child(scan_oper);

  ProjectOperator project_oper;
  project_oper.add_child(&pred_oper);
//  for (const Field &field : select_stmt->query_fields()) {
//    project_oper.add_projection(field.field_name(), nullptr, false);
//  }
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
  session_event->set_response(ss.str());
  return rc;
}


