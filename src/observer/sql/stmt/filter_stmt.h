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
// Created by Wangyunlai on 2022/5/22.
//

#pragma once

#include <vector>
#include <unordered_map>
#include "rc.h"
#include "sql/parser/parse_defs.h"
#include "sql/stmt/stmt.h"
#include "sql/expr/expression.h"
#include "common/log/log.h"
#include "sql/expr/tuple.h"
#include "util/comparator.h"

class Db;
class Table;
class FieldMeta;

class FilterUnit
{
public:
  FilterUnit() = default;
  ~FilterUnit()
  {
    if (left_) {
      delete left_;
      left_ = nullptr;
    }
    if (right_) {
      delete right_;
      right_ = nullptr;
    }
  }

  bool compare(Tuple* t1 = nullptr, Tuple* t2 = nullptr) {
    TupleCell left_cell, right_cell;
    if (t1 == nullptr && t2 == nullptr) {
      if (left_->type() != ExprType::VALUE || right_->type() != ExprType::VALUE) {
        //todo 错误处理
        LOG_WARN("[FilterUnit::compare] invalid parameter, if params are null, the exprType of filterUnit both should be value");
        return false;
      }
      RowTuple temp;
      left_->get_value(temp, left_cell);
      right_->get_value(temp, right_cell);
    } else if (t1 != nullptr && t2 != nullptr) {
      left_->get_value(*t1, left_cell);
      right_->get_value(*t2, right_cell);
    } else if (t1 != nullptr && t2 == nullptr){
      left_->get_value(*t1, left_cell);
      right_->get_value(*t1, right_cell);
    } else {
      //todo 错误处理
      LOG_WARN("[FilterUnit::compare] invalid parameter");
      return false;
    }

    if (comp_ == LIKE || comp_ == NOT_LIKE) {
      if (left_cell.attr_type() == AttrType::CHARS && right_cell.attr_type() == AttrType::CHARS) {
        bool flag = compare_string((void *)left_cell.data(), left_cell.length(), (void *)right_cell.data(), right_cell.length(), true);
        if ((comp_ == LIKE && flag) || (comp_ == NOT_LIKE && !flag)) {
          return true;
        }
      }
      //todo(hjh) 这里到底是返回client failure还是false
      return false;
    }


    const int compare = left_cell.compare(right_cell);
    bool filter_result = false;
    switch (comp_) {
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
        LOG_WARN("invalid compare type: %d", comp_);
      } break;
    }
    if (!filter_result) {
      return false;
    }
    return true;
  }
  
  void set_comp(CompOp comp) {
    comp_ = comp;
  }

  CompOp comp() const {
    return comp_;
  }

  void set_left(Expression *expr)
  {
    left_ = expr;
  }
  void set_right(Expression *expr)
  {
    right_ = expr;
  }
  Expression *left() const
  {
    return left_;
  }
  Expression *right() const
  {
    return right_;
  }

private:
  CompOp comp_ = NO_OP;
  Expression *left_ = nullptr;
  Expression *right_ = nullptr;
};

class FilterStmt 
{
public:

  FilterStmt() = default;
  virtual ~FilterStmt();

public:
  const std::vector<FilterUnit *> &filter_units() const
  {
    return filter_units_;
  }

public:
  static RC create(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables,
			const Condition *conditions, int condition_num,
			FilterStmt *&stmt);

  static RC create_filter_unit(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables,
			       const Condition &condition, FilterUnit *&filter_unit);

private:
  std::vector<FilterUnit *>  filter_units_; // 默认当前都是AND关系
};
