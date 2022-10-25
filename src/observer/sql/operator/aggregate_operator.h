//
// Created by Joenhle on 2022/10/22.
//

#pragma once

#include "sql/parser/parse.h"
#include "sql/operator/operator.h"
#include "rc.h"
#include "sql/stmt/filter_stmt.h"
#include <vector>
#include <unordered_map>

using namespace std;

class AggregateField {
public:
  AggregationType op_type = AggregationType::NO_Aggregation;
  TupleCellSpec aggregate_field;
};

class innerRes {
public:
  TupleCell max_value;
  TupleCell min_value;
  float sum = 0;
  int count = 0;
};

class AggregateOperator : public Operator
{

public:
  AggregateOperator(vector<AggregateField> aggregate_ops, vector<TupleCellSpec> groupby_fields) : aggregate_ops_(aggregate_ops), groupby_fields_(groupby_fields){};
  virtual ~AggregateOperator() = default;
  RC open() override;
  RC next() override;
  RC close() override;
  Tuple* current_tuple() override { return &tuple_; };

private:
  RC mergeTupleIntoGroup(VTuple &tuple);

private:
  vector<AggregateField> aggregate_ops_;
  vector<TupleCellSpec> groupby_fields_;
  VTuple tuple_;
  unordered_map<string, vector<innerRes*>*>::iterator iter;
  unordered_map<string, vector<innerRes*>*> innerResMap;
};