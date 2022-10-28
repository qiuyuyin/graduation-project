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

  ProjectOperator(vector<shared_ptr<TupleCellSpec>> projections) : projections_(projections){}
  void add_projection(shared_ptr<TupleCellSpec>& projection);

  RC open() override;
  RC next() override;
  RC close() override;

  const vector<shared_ptr<TupleCellSpec>> projections() const { return projections_; };

  Tuple * current_tuple() override;
private:
  VTuple tuple_;
  vector<shared_ptr<TupleCellSpec>> projections_;
};
