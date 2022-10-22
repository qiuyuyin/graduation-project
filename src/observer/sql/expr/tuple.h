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
// Created by Wangyunlai on 2021/5/14.
//

#pragma once

#include <memory>
#include <vector>

#include "common/log/log.h"
#include "sql/parser/parse.h"
#include "sql/expr/tuple_cell.h"
#include "sql/expr/expression.h"
#include "storage/record/record.h"

class Table;
class VTuple;

class TupleCellSpec {

  friend VTuple;

public:
  TupleCellSpec() = default;
  TupleCellSpec(Expression *expr) : expression_(expr)
  {}

  ~TupleCellSpec()
  {
    if (expression_) {
      delete expression_;
      expression_ = nullptr;
    }
  }

  void set_alias(const char *alias)
  {
    this->alias_ = alias;
  }
  const char *alias() const
  {
    return alias_;
  }

  Expression *expression() const
  {
    return expression_;
  }

private:
  const char *alias_ = nullptr;
  Expression *expression_ = nullptr;
  size_t offset;
};

class Tuple {
public:
  Tuple() = default;
  virtual ~Tuple() = default;

  virtual int cell_num() const = 0;
  virtual RC cell_at(int index, TupleCell &cell) const = 0;
  virtual RC find_cell(const Field &field, TupleCell &cell) const = 0;

  virtual RC cell_spec_at(int index, const TupleCellSpec *&spec) const = 0;
};

class RowTuple : public Tuple {
public:
  RowTuple() = default;
  virtual ~RowTuple()
  {
    for (TupleCellSpec *spec : speces_) {
      delete spec;
    }
    speces_.clear();
  }

  void set_record(Record *record)
  {
    this->record_ = record;
  }

  void set_schema(const Table *table, const std::vector<FieldMeta> *fields)
  {
    table_ = table;
    this->speces_.reserve(fields->size());
    for (const FieldMeta &field : *fields) {
      speces_.push_back(new TupleCellSpec(new FieldExpr(table, &field)));
    }
  }

  int cell_num() const override
  {
    return speces_.size();
  }

  RC cell_at(int index, TupleCell &cell) const override
  {
    if (index < 0 || index >= static_cast<int>(speces_.size())) {
      LOG_WARN("invalid argument. index=%d", index);
      return RC::INVALID_ARGUMENT;
    }

    const TupleCellSpec *spec = speces_[index];
    FieldExpr *field_expr = (FieldExpr *)spec->expression();
    const FieldMeta *field_meta = field_expr->field().meta();
    cell.set_type(field_meta->type());
    cell.set_data(this->record_->data() + field_meta->offset());
    cell.set_length(field_meta->len());
    return RC::SUCCESS;
  }

  RC find_cell(const Field &field, TupleCell &cell) const override
  {
    const char *table_name = field.table_name();
    if (0 != strcmp(table_name, table_->name())) {
      return RC::NOTFOUND;
    }

    const char *field_name = field.field_name();
    for (size_t i = 0; i < speces_.size(); ++i) {
      const FieldExpr *field_expr = (const FieldExpr *)speces_[i]->expression();
      const Field &field = field_expr->field();
      if (0 == strcmp(field_name, field.field_name())) {
        return cell_at(i, cell);
      }
    }
    return RC::NOTFOUND;
  }

  RC cell_spec_at(int index, const TupleCellSpec *&spec) const override
  {
    if (index < 0 || index >= static_cast<int>(speces_.size())) {
      LOG_WARN("invalid argument. index=%d", index);
      return RC::INVALID_ARGUMENT;
    }
    spec = speces_[index];
    return RC::SUCCESS;
  }

  Record &record()
  {
    return *record_;
  }

  const Record &record() const
  {
    return *record_;
  }

private:
  Record *record_ = nullptr;
  const Table *table_ = nullptr;
  std::vector<TupleCellSpec *> speces_;
};

class VTuple : public Tuple {
public:
  ~VTuple() override = default;
  int cell_num() const override
  {
    return speces_.size();
  }
  RC cell_at(int index, TupleCell &cell) const override
  {
    if (index < 0 || index >= static_cast<int>(speces_.size())) {
      LOG_WARN("invalid argument. index=%d", index);
      return RC::INVALID_ARGUMENT;
    }

    const TupleCellSpec *spec = speces_[index];
    switch (spec->expression()->type()) {
      case ExprType::FIELD: {
        FieldExpr *field_expr = (FieldExpr *)spec->expression();
        const FieldMeta *field_meta = field_expr->field().meta();
        cell.set_type(field_meta->type());
        cell.set_data(this->data_ + spec->offset);
        cell.set_length(field_meta->len());
        return RC::SUCCESS;
      }
      case ExprType::VALUE: {
        ValueExpr *value_expr = (ValueExpr *)spec->expression();
        value_expr->get_tuple_cell(cell);
        return RC::SUCCESS;
      }
    }
  }
  RC find_cell(const Field &field, TupleCell &cell) const override
  {

    const char *field_name = field.field_name();
    for (size_t i = 0; i < speces_.size(); ++i) {
      if(speces_[i]->expression()->type() == ExprType::FIELD){
        const FieldExpr *field_expr = (const FieldExpr *)speces_[i]->expression();
        const Field &field = field_expr->field();
        if (0 == strcmp(field_name, field.field_name())) {
          return cell_at(i, cell);
        }
      }
    }
    return RC::NOTFOUND;
  }
  RC find_cell(const TupleCellSpec& spec, TupleCell& cell) {
    switch (spec.expression()->type()) {
      case ExprType::FIELD:{
        auto expr = static_cast<FieldExpr*>(spec.expression());
        return find_cell(expr->field(), cell);
      }
      case ExprType::VALUE:{
        auto expr = static_cast<ValueExpr*>(spec.expression());
        expr->get_tuple_cell(cell);
        return RC::SUCCESS;
      }
      default:
        return RC:: UNIMPLENMENT;
    }
  }
  RC cell_spec_at(int index, const TupleCellSpec *&spec) const override
  {
    if (index < 0 || index >= static_cast<int>(speces_.size())) {
      LOG_WARN("invalid argument. index=%d", index);
      return RC::INVALID_ARGUMENT;
    }
    spec = speces_[index];
    return RC::SUCCESS;
  }
  std::vector<TupleCellSpec *> schema()
  {
    return speces_;
  }
  RC merge(VTuple &other, VTuple &out)
  {
    size_t data_len = data_len_ + other.data_len_;
    int offset = 0;
    char *const data = new char[data_len];
    size_t this_sz = speces_.size();
    size_t other_sz = other.speces_.size();

    out.data_len_ = data_len;
    out.data_ = data;
    out.speces_.resize(speces_.size() + other.speces_.size());
    for (int i = 0; i < this_sz; ++i) {
      out.speces_[i] = speces_[i];
      out.speces_[i]->offset = offset;
      if (out.speces_[i]->expression()->type() == ExprType::FIELD) {
        auto field_expr = static_cast<FieldExpr *>(out.speces_[i]->expression());
        offset += field_expr->field().meta()->len();
      }
    }
    for (int i = 0; i < other_sz; i++) {
      int idx = i + this_sz;
      out.speces_[idx] = other.speces_[idx];
      if (out.speces_[idx]->expression()->type() == ExprType::FIELD) {
        auto field_expr = static_cast<FieldExpr *>(out.speces_[idx]->expression());
        offset += field_expr->field().meta()->len();
      }
    }
    memcpy(data, data_, data_len_);
    memcpy(data+data_len_, other.data_, other.data_len_);
  }

private:
  char *data_ = nullptr;
  size_t data_len_ = 0;
  std::vector<TupleCellSpec *> speces_;
};
/*
class CompositeTuple : public Tuple
{
public:
  int cell_num() const override;
  RC  cell_at(int index, TupleCell &cell) const = 0;
private:
  int cell_num_ = 0;
  std::vector<Tuple *> tuples_;
};
*/

class ProjectTuple : public Tuple {
public:
  ProjectTuple() = default;
  virtual ~ProjectTuple()
  {
    for (TupleCellSpec *spec : speces_) {
      delete spec;
    }
    speces_.clear();
  }

  void set_tuple(Tuple *tuple)
  {
    this->tuple_ = tuple;
  }

  void add_cell_spec(TupleCellSpec *spec)
  {
    speces_.push_back(spec);
  }
  int cell_num() const override
  {
    return speces_.size();
  }

  RC cell_at(int index, TupleCell &cell) const override
  {
    if (index < 0 || index >= static_cast<int>(speces_.size())) {
      return RC::GENERIC_ERROR;
    }
    if (tuple_ == nullptr) {
      return RC::GENERIC_ERROR;
    }

    const TupleCellSpec *spec = speces_[index];
    return spec->expression()->get_value(*tuple_, cell);
  }

  RC find_cell(const Field &field, TupleCell &cell) const override
  {
    return tuple_->find_cell(field, cell);
  }
  RC cell_spec_at(int index, const TupleCellSpec *&spec) const override
  {
    if (index < 0 || index >= static_cast<int>(speces_.size())) {
      return RC::NOTFOUND;
    }
    spec = speces_[index];
    return RC::SUCCESS;
  }

private:
  std::vector<TupleCellSpec *> speces_;
  Tuple *tuple_ = nullptr;
};
