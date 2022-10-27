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

#include "common/log/log.h"
#include "sql/operator/project_operator.h"
#include "storage/record/record.h"
#include "storage/common/table.h"

RC ProjectOperator::open()
{
  if (children_.size() != 1) {
    LOG_WARN("project operator must has 1 child");
    return RC::INTERNAL;
  }

  Operator *child = children_[0];
  RC rc = child->open();
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to open child operator: %s", strrc(rc));
    return rc;
  }

  return RC::SUCCESS;
}

RC ProjectOperator::next()
{
  RC rc;
  if ((rc = children_[0]->next()) == SUCCESS) {
    RowTuple *trans = dynamic_cast<RowTuple *>(children_[0]->current_tuple());
    VTuple *temp = new VTuple;
    temp->append_row_tuple(*trans);
    VTuple res;
    for (const auto& projection : projections_) {
      TupleCell cell;
      if ((rc = temp->find_cell(*projection, cell)) != SUCCESS) {
        LOG_WARN("[projection::next] tupleCell::find_cell error");
        return rc;
      }
      string field_name = projection->expr_name();
      if (projection->alias() != nullptr) {
        field_name = projection->alias();
      }
      //todo 这里的type采用哪一种呢？是projection的还是cell的
      if ((rc = res.append_var(field_name, cell.attr_type(), cell.length(), (void *)cell.data())) != SUCCESS) {
        LOG_WARN("[projection::next] Vtuple::append_var_tuple error");
        return rc;
      }
    }
    tuple_ = res;
  }
  return rc;
}

RC ProjectOperator::close()
{
  children_[0]->close();
  return RC::SUCCESS;
}
Tuple *ProjectOperator::current_tuple()
{
  return &tuple_;
}

void ProjectOperator::add_projection(TupleCellSpec *tuple_cell_spec)
{
  projections_.push_back(tuple_cell_spec);
}
