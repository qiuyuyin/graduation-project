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

void dfs(stringstream& ss, vector<Operator*>& tuple_sets, unordered_map<string, int>& table_index, vector<vector<Field>>& projection_fields,
    vector<vector<FilterUnit*>> &single_filters, unordered_map<int, vector<pair<int, FilterUnit*>>>& cross_filters, vector<Tuple*>& merge_tuple, int step) {
  int table_num = static_cast<int>(table_index.size());
  if (step == table_num) {
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
    return;
  }

  Operator *&current_operator = tuple_sets[step];
  current_operator->open();
  RC rc = RC::SUCCESS;
  while ((rc = current_operator->next()) == RC::SUCCESS) {
    Tuple *current_tuple = current_operator->current_tuple();
    bool flag = true;
    for (auto filter_unit : single_filters[step]) {
      if (!filter_unit->compare(current_tuple)) {
        flag = false;
        break;
      }
    }

    for (auto p : cross_filters[step]) {
      int prev_index = p.first;
      Tuple *&prev_tuple = merge_tuple[prev_index];
      auto filter_unit = p.second;
      int &left_index = table_index[string((*(FieldExpr *)filter_unit->left()).table_name())];
      if (prev_index == left_index) {
        if (!filter_unit->compare(prev_tuple, current_tuple)) {
          flag = false;
          break;
        }
      } else {
        if (!filter_unit->compare(current_tuple, prev_tuple)) {
          flag = false;
          break;
        }
      }
    }

    if (flag) {
      merge_tuple.push_back(current_tuple);
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
  unordered_map<int, vector<pair<int, FilterUnit*>>> cross_filters;


  vector<FilterUnit*> both_value_filters;
  for (auto filter_unit : select_stmt.filter_stmt()->filter_units()) {
    Expression *left = filter_unit->left();
    Expression *right = filter_unit->right();
    FieldExpr* fieldExpr = nullptr;
    if (left->type() == ExprType::FIELD && right->type() == ExprType::FIELD) {
      int index_left = table_index[string(((FieldExpr*)left)->table_name())];
      int index_right = table_index[string(((FieldExpr*)right)->table_name())];
      int bigger_index = max(index_left, index_right);
      int smaller_index = min(index_left, index_right);
      if (cross_filters.count(bigger_index) == 0) {
        vector<pair<int, FilterUnit*>> temp;
        cross_filters[bigger_index] = vector<pair<int, FilterUnit*>>();
      }
      cross_filters[bigger_index].push_back({smaller_index, filter_unit});
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



RC print_aggregation_tuple(stringstream& ss, Operator* op, SelectStmt& select_stmt) {

  auto field = select_stmt.query_fields()[0];
  auto aggregation_type = select_stmt.aggregation_funcs()[0];
  if ((aggregation_type == AggregationType::COUNT) &&
      ((strcmp(field.field_name(), "1") != 0 && strcmp(field.field_name(), "*") != 0)) &&
      ((select_stmt.tables()[0]->table_meta().field(field.field_name()) == nullptr))) {
    LOG_WARN("%s isn't the field of table %s", field.field_name(), select_stmt.tables()[0]->name());
    return INVALID_ARGUMENT;
  }

  // print header
  int size = select_stmt.query_fields().size();
  string header;
  for (int i = 0; i < size; ++i) {
    field = select_stmt.query_fields()[i];
    aggregation_type = select_stmt.aggregation_funcs()[i];
    if (aggregation_type == MAX) { header += "max(" + string(field.field_name()) + ")"; }
    if (aggregation_type == MIN) { header += "min(" + string(field.field_name()) + ")"; }
    if (aggregation_type == COUNT) { header += "count(" + string(field.field_name()) + ")"; }
    if (aggregation_type == AVG) { header += "avg(" + string(field.field_name()) + ")"; }
    if (aggregation_type == SUM) { header += "sum(" + string(field.field_name()) + ")"; }
    if (i == size-1) {
      header += "\n";
    } else {
      header += " | ";
    }
  }

  auto tuple_value2float = [&](TupleCell& tupleCell){
    float data = 0;
    if (field.attr_type() == AttrType::INTS) {
      data = (float)*(int *)tupleCell.data();
    } else if (field.attr_type() == AttrType::FLOATS) {
      data = *(float *)tupleCell.data();
    } else if (field.attr_type() == AttrType::CHARS) {
      data = Typecaster::s2f(tupleCell.data());
    }
    return data;
  };
  string body;
  for (int i = 0; i < size; ++i) {
    stringstream temp;
    field = select_stmt.query_fields()[i];
    aggregation_type = select_stmt.aggregation_funcs()[i];
    op->open();
    RC rc;
    TupleCell max_cell, min_cell, temp_cell;
    Tuple* tuple = nullptr;
    float sum = 0;
    int count = 0;
    if ((rc = op->next()) == RC::SUCCESS) {
      count += 1;
      if (aggregation_type != AggregationType::COUNT) {
        tuple = op->current_tuple();
        tuple->find_cell(field, temp_cell);
        max_cell = temp_cell;
        min_cell = temp_cell;
        sum += tuple_value2float(temp_cell);
      }
    }
    while ((rc = op->next()) == RC::SUCCESS) {
      if (aggregation_type == AggregationType::COUNT) {
        count += 1;
        continue;
      }
      tuple = op->current_tuple();
      tuple->find_cell(field, temp_cell);
      if (temp_cell.compare(max_cell) > 0) { max_cell = temp_cell; }
      if (temp_cell.compare(min_cell) <0 ) { min_cell = temp_cell; }
      count += 1;
      sum += tuple_value2float(temp_cell);
    }
    switch (aggregation_type) {
      case MAX:
        if (count > 0) {
          max_cell.to_string(temp);
          body += temp.str();
        } else {
          body += "0";
        }
        break;
      case MIN:
        if (count > 0) {
          min_cell.to_string(temp);
          body += temp.str();
        } else {
          body += "0";
        }
        break;
      case COUNT:
        body += to_string(count);
        break;
      case AVG:
        body += double2string(sum/(float)count);
        break;
      case SUM:
        if (field.attr_type() == AttrType::INTS || field.attr_type() == AttrType::CHARS) {
          body += to_string((int)sum);
        } else {
          body += double2string(sum);
        }
        break;
      default:
        LOG_WARN("no support aggregation_type %d", aggregation_type);
        return INVALID_ARGUMENT;
    }
    if (i == size-1) {
      body += "\n";
    } else {
      body += " | ";
    }
    op->close();
  }
  ss << header << body;
  return SUCCESS;
}


RC ExecuteStage::do_select(SQLStageEvent *sql_event)
{
  SelectStmt *select_stmt = (SelectStmt *)(sql_event->stmt());
  SessionEvent *session_event = sql_event->session_event();
  RC rc = RC::SUCCESS;
  stringstream ss;

  // 多表的查询
  if (select_stmt->tables().size() != 1) {
    int table_num = select_stmt->tables().size();
    vector<Operator*> tuple_list;
    for (int i = 0; i < table_num; ++i) {
      //todo(hjh) 先直接进行scan扫描，后面多列索引实现了再优化
      Operator* scan_oper = new TableScanOperator(select_stmt->tables()[i]);
      tuple_list.push_back(scan_oper);
    }
    rc = print_tuple_sets(ss, tuple_list, *select_stmt);
    for (auto oper : tuple_list) {
      oper->close();
      delete oper;
    }
    if (rc == SUCCESS) {
      session_event->set_response(ss.str());
    } else {
      session_event->set_response("FAILURE\n");
    }
    return rc;
  }

  Operator *scan_oper = try_to_create_index_scan_operator(select_stmt->filter_stmt());
  if (nullptr == scan_oper) {
    scan_oper = new TableScanOperator(select_stmt->tables()[0]);
  }

  DEFER([&] () {delete scan_oper;});
  PredicateOperator pred_oper(select_stmt->filter_stmt());
  pred_oper.add_child(scan_oper);

  // 聚合函数查询
  if (select_stmt->aggregation_funcs().size() > 0) {
    rc = print_aggregation_tuple(ss, &pred_oper, *select_stmt);
    if (rc == SUCCESS) {
      session_event->set_response(ss.str());
    } else {
      session_event->set_response("FAILURE\n");
    }
    return rc;
  }

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


