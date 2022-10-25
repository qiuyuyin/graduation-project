//
// Created by sheep on 2022/10/22.
//

#pragma once

#include "sql/operator/operator.h"
#include "rc.h"
#include <algorithm>

class OrderByField {
public:
  OrderType od_type = OrderType ::ASC_ORDER;
  TupleCellSpec orderby_field;
};


class SortOperator : public Operator
{
public:
  SortOperator(vector<OrderByField> od_fields): orderby_fields_(od_fields)
  {}

  virtual ~SortOperator() = default;

  RC open() override;
  RC next() override;
  RC close() override;

  Tuple* current_tuple() override { return *iter; };

private:
  void tupleSort();

private:
  vector<VTuple *> tuple_set;
  vector<VTuple *>::iterator iter;
  vector<OrderByField> orderby_fields_;
};

typedef struct{
  VTuple tuple_;
  vector<OrderByField> odb_fields;
} VTuple4Sort;

bool compare_for_sort(VTuple4Sort arg1,VTuple4Sort arg2);


