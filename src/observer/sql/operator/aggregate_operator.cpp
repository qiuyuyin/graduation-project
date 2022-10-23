//
// Created by Joenhle on 2022/10/22.
//

#include "sql/operator/aggregate_operator.h"
#include <numeric>
#include "sql/stmt/typecaster.h"
#include "util/util.h"

RC AggregateOperator::open()
{
  if (children_.size() != 1) {
    LOG_WARN("aggregate operator must has one child");
    return RC::INTERNAL;
  }
  RC rc;
  if ((rc = children_[0]->open()) != SUCCESS) {
    LOG_WARN("aggregate operator's children open error");
    return rc;
  }

  while ((rc = children_[0]->next()) == SUCCESS) {
    VTuple temp = *(VTuple*)children_[0]->current_tuple();
    if ((rc = mergeTupleIntoGroup(temp)) != SUCCESS) {
      return rc;
    }
  }
  if (rc == RECORD_EOF) {
    iter = innerResMap.begin();
    rc = SUCCESS;
  }
  return rc;
}

RC AggregateOperator::close()
{
  RC rc;
  if ((rc = children_[0]->close()) != SUCCESS) {
    LOG_WARN("aggregate operator's children close error");
    return rc;
  }
  return SUCCESS;
}

RC AggregateOperator::next()
{
  if (iter == innerResMap.end()) {
    return RECORD_EOF;
  }
  string key = iter->first;
  auto innerRes = iter->second;
  vector<string> group_values = split(key, "_");
  for (int i = 0; i < aggregate_ops_.size(); ++i) {
    auto agg_op = aggregate_ops_.at(i);
    auto agg_res = innerRes->at(i);
    string field_name = string(aggregate_type_to_string(agg_op.op_type)) + "(";
    if (agg_op.aggregate_field.table_name() != "") {
      field_name += agg_op.aggregate_field.table_name() + ".";
    }
    field_name += agg_op.aggregate_field.expr_name() + ")";
    AttrType field_type = agg_op.aggregate_field.attr_type();
    void* data;
    switch (agg_op.op_type) {
      case MAX:
        data = const_cast<char*>(agg_res->max_value.data());
        break;
      case MIN:
        data = const_cast<char*>(agg_res->min_value.data());
        break;
      case COUNT:
      {
        int *temp = new int(agg_res->count);
        data = temp;
        field_type = INTS;
        break;
      }
      case SUM:
        if (field_type == INTS) {
          int *temp = new int(agg_res->sum);
          data = temp;
        } else {
          field_type = FLOATS;
          float* temp = new float(agg_res->sum);
          data = temp;
        }
        break;
      case AVG:
      {
        field_type = FLOATS;
        float* temp = new float(agg_res->sum/(float)agg_res->count);
        data = temp;
        break;
      }
      default:
        return INVALID_ARGUMENT;
    }
    tuple_.append_var(field_name, field_type, data);
  }
  for (int i = 0; i < groupby_fields_.size(); ++i) {
    void* data = const_cast<char*>(group_values[i].c_str());
    tuple_.append_var(groupby_fields_.at(i).expr_name(), groupby_fields_.at(i).attr_type(), data);
  }
  iter++;
  return SUCCESS;
}

RC AggregateOperator::mergeTupleIntoGroup(VTuple &tuple)
{
  RC rc;
  string key;
  if (groupby_fields_.empty()) {
    key = "no_group";
  }

  for (int i = 0; i < groupby_fields_.size(); ++i) {
    auto groupby_field = groupby_fields_[i];
    TupleCell tupleCell;
    if ((rc = tuple.find_cell(groupby_field, tupleCell)) != SUCCESS) {
      return rc;
    }
    key += tupleCell.to_string();
    if (i < groupby_fields_.size()-1) {
      key += "_";
    }
  }
  if (innerResMap.count(key) == 0) {
    innerResMap[key] = new vector<innerRes*>(aggregate_ops_.size());
  }

  auto tuple_value2float = [](AttrType field_type, TupleCell& tupleCell){
    float data = 0;
    if (field_type == AttrType::INTS) {
      data = (float)*(int *)tupleCell.data();
    } else if (field_type == AttrType::FLOATS) {
      data = *(float *)tupleCell.data();
    } else if (field_type == AttrType::CHARS) {
      data = Typecaster::s2f(tupleCell.data());
    }
    return data;
  };

  auto inner_res = innerResMap[key];
  for (int i = 0; i < aggregate_ops_.size(); ++i) {
    auto agg_type = aggregate_ops_[i].op_type;
    auto tuple_cell_spec = aggregate_ops_[i].aggregate_field;
    auto inner = inner_res->at(i);
    if (agg_type == NO_Aggregation) {
      return INVALID_ARGUMENT;
    }
    inner->count += 1;
    if (agg_type == COUNT) {
      continue;
    }
    TupleCell temp;
    if ((rc = tuple.find_cell(aggregate_ops_[i].aggregate_field, temp)) != SUCCESS) {
      return rc;
    }
    if (inner->max_value.data() == nullptr || temp.compare(inner->max_value) > 0) {
      inner->max_value = temp;
    }
    if (inner->min_value.data() == nullptr || temp.compare(inner->min_value) < 0) {
      inner->min_value = temp;
    }
    inner->sum += tuple_value2float(tuple_cell_spec.attr_type(), temp);
  }
  return SUCCESS;
}