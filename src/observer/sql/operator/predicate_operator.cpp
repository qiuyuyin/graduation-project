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
// Created by WangYunlai on 2022/6/27.
//

#include "common/log/log.h"
#include "sql/operator/predicate_operator.h"
#include "storage/record/record.h"
#include "sql/stmt/filter_stmt.h"
#include "storage/common/field.h"
#include "util/comparator.h"

RC PredicateOperator::open()
{
  if (children_.size() != 1) {
    LOG_WARN("predicate operator must has one child");
    return RC::INTERNAL;
  }
  return children_[0]->open();
}

RC PredicateOperator::next()
{
  RC rc = RC::SUCCESS;
  Operator *oper = children_[0];
  
  while (RC::SUCCESS == (rc = oper->next())) {
    auto tuple = oper->current_tuple();
    if (nullptr == tuple) {
      rc = RC::INTERNAL;
      LOG_WARN("failed to get tuple from operator");
      break;
    }

    if (do_predicate(tuple)) {
      return rc;
    }
  }
  return rc;
}

RC PredicateOperator::close()
{
  children_[0]->close();
  return RC::SUCCESS;
}

Tuple * PredicateOperator::current_tuple()
{
  return children_[0]->current_tuple();
}

bool PredicateOperator::do_predicate(Tuple* t1)
{
  if (filter_units_.empty()) {
    return true;
  }
  for (auto filter_unit : filter_units_) {
    TupleCell left_cell, right_cell;
    auto left = filter_unit->left();
    auto right = filter_unit->right();
    auto comp = filter_unit->comp();
    if (t1 == nullptr) {
      if (left->type() != ExprType::VALUE || right->type() != ExprType::VALUE) {
        LOG_WARN("[FilterUnit::compare] invalid parameter, if params are null, the exprType of filterUnit both should be value");
        return false;
      }
      VTuple temp;
      left->get_value(temp, left_cell);
      right->get_value(temp, right_cell);
    } else {
      left->get_value(*t1, left_cell);
      right->get_value(*t1, right_cell);
    }
    if (comp == LIKE || comp == NOT_LIKE) {
      if (left_cell.attr_type() == AttrType::CHARS && right_cell.attr_type() == AttrType::CHARS) {
        bool flag = compare_string((void *)left_cell.data(), left_cell.length(), (void *)right_cell.data(), right_cell.length(), true);
        if ((comp == LIKE && flag) || (comp == NOT_LIKE && !flag)) {
          return true;
        }
      }
      //todo(hjh) 这里到底是返回client failure还是false
      return false;
    }

    // check null compare
    auto compare_null = [](TupleCell& c1, TupleCell& c2, CompOp op){
      if (op == IS) return c1.is_null();
      if (op == IS_NOT) return !c1.is_null();
      return false;
    };

    if (left_cell.attr_type() == UNDEFINED && right_cell.attr_type() == UNDEFINED) {
      if (comp == IS) return true;
      if (comp == IS_NOT) return false;
      return false;
    } else if (left_cell.attr_type() != UNDEFINED && right_cell.attr_type() == UNDEFINED) {
      return compare_null(left_cell, right_cell, comp);
    } else if (left_cell.attr_type() == UNDEFINED && right_cell.attr_type() != UNDEFINED) {
      return compare_null(right_cell, left_cell, comp);
    }



    const int compare = left_cell.compare(right_cell);
    bool filter_result = false;
    switch (comp) {
      case EQUAL_TO: {
        filter_result = (0 == compare);
      } break;
      case LESS_EQUAL: {
        filter_result = (compare <= 0);
      } break;
      case NOT_EQUAL: {
        filter_result = (compare != 0);
      } break;
      case LESS_THAN: {
        filter_result = (compare < 0);
      } break;
      case GREAT_EQUAL: {
        filter_result = (compare >= 0);
      } break;
      case GREAT_THAN: {
        filter_result = (compare > 0);
      } break;
      default: {
        LOG_WARN("invalid compare type: %d", comp);
      } break;
    }
    if (!filter_result) {
      return false;
    }
  }
  return true;
}