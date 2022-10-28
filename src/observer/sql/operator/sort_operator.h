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
  shared_ptr<TupleCellSpec> orderby_field;
};

enum ResIterType{
  BEFORE_BEGIN,
  ON_WAY,
  AFTER_END,
};

typedef struct{
  VTuple* tuple_data;
  vector<OrderByField> odb_fields;
} Tuple4Sort;

class SortOperator : public Operator
{
public:
  SortOperator(vector<OrderByField> od_fields): orderby_fields_(od_fields)
  {}

  virtual ~SortOperator() = default;

  RC open() override;
  RC next() override;
  RC close() override;

  Tuple* current_tuple() override { return tuple_set[tuple_index]; };

private:
  void tupleSort();

private:
  vector<VTuple *> tuple_set;
  int tuple_index ;
  vector<OrderByField> orderby_fields_;
  ResIterType res_iter_type;
  vector<Tuple4Sort> sort_tuple_set;
};



bool compare_for_sort(Tuple4Sort arg1,Tuple4Sort arg2);


