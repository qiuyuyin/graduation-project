/* Copyright (c) 2021 Xie Meiyi(xiemeiyi@hust.edu.cn) and OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by WangYunlai on 2022/07/01.
//

#pragma once

#include "sql/operator/operator.h"
#include "rc.h"

class ProjectOperator : public Operator
{
public:
  virtual ~ProjectOperator() = default;
  void add_projection(TupleCellSpec *tuple_cell_spec);

  RC open() override;
  RC next() override;
  RC close() override;

  const vector<TupleCellSpec*>* projections() const { return &projections_; };

  Tuple * current_tuple() override;
private:
  VTuple tuple_;
  vector<TupleCellSpec *> projections_;
};
