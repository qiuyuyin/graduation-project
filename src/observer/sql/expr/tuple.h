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

  std::string table_name()
  {
    if (expression_ == nullptr) {
      return "";
    }
    switch (expression_->type()) {
      case ExprType::FIELD: {
        auto expr = static_cast<FieldExpr *>(expression_);
        return expr->table_name();
      }
      case ExprType::VALUE:
        return "";
    }
  }

  AttrType attr_type()
  {
    if (expression_ == nullptr) {
      return AttrType::UNDEFINED;
    }
    switch (expression_->type()) {
      case ExprType::FIELD: {
        auto expr = static_cast<FieldExpr *>(expression_);
        return expr->field().meta()->type();
      }
      case ExprType::VALUE: {
        auto expr = static_cast<ValueExpr *>(expression_);
        return expr->tuple_cell_.attr_type();
      }
    }
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
  VTuple(size_t size)
  {
    schema_.resize(size);
    cells_.resize(size);
  }
  ~VTuple() override = default;
  int cell_num() const override
  {
    return schema_.size();
  }
  RC cell_at(int index, TupleCell &cell) const override
  {
    if (index < 0 || index >= static_cast<int>(schema_.size())) {
      LOG_WARN("invalid argument. index=%d", index);
      return RC::INVALID_ARGUMENT;
    }

    cell = cells_[index];
    return RC::SUCCESS;
  }
  RC find_cell(const Field &field, TupleCell &cell) const override
  {
    const char *field_name = field.field_name();
    for (size_t i = 0; i < schema_.size(); ++i) {
      if (schema_[i]->expression()->type() == ExprType::FIELD) {
        const FieldExpr *field_expr = (const FieldExpr *)schema_[i]->expression();
        const Field &field = field_expr->field();
        if (0 == strcmp(field_name, field.field_name())) {
          return cell_at(i, cell);
        }
      }
    }
    return RC::NOTFOUND;
  }
  RC find_cell(const TupleCellSpec &spec, TupleCell &cell)
  {
    switch (spec.expression()->type()) {
      case ExprType::FIELD: {
        auto expr = static_cast<FieldExpr *>(spec.expression());
        return find_cell(expr->field(), cell);
      }
      case ExprType::VALUE: {
        auto expr = static_cast<ValueExpr *>(spec.expression());
        expr->get_tuple_cell(cell);
        return RC::SUCCESS;
      }
      default:
        return RC::UNIMPLENMENT;
    }
  }
  RC cell_spec_at(int index, const TupleCellSpec *&spec) const override
  {
    if (index < 0 || index >= static_cast<int>(schema_.size())) {
      LOG_WARN("invalid argument. index=%d", index);
      return RC::INVALID_ARGUMENT;
    }
    spec = schema_[index];
    return RC::SUCCESS;
  }
  void append_cell(TupleCell &cell, TupleCellSpec *spec)
  {
    cells_.push_back(cell);
    schema_.push_back(spec);
  }
  RC append_row_tuple(RowTuple &row)
  {
    int cells = row.cell_num();
    for (int i = 0; i < cells; i++) {
      TupleCell cell;
      const TupleCellSpec *spec;
      row.cell_at(i, cell);
      row.cell_spec_at(i, spec);
      cells_.push_back(cell);
      schema_.push_back(const_cast<TupleCellSpec *>(spec));
    }
  }
  RC set_field(int index, TupleCell &cell, TupleCellSpec *spec)
  {
    if (index < 0 || index >= static_cast<int>(schema_.size())) {
      LOG_WARN("invalid argument. index=%d", index);
      return RC::INVALID_ARGUMENT;
    }

    free_spec(schema_[index]);

    cells_[index] = cell;
    schema_[index] = spec;
    return RC::SUCCESS;
  }
  RC set_value(int index, Value &value)
  {
    auto expr = new ValueExpr(value);
    TupleCellSpec *spec = new TupleCellSpec(expr);
    TupleCell cell;

    expr->get_tuple_cell(cell);
    allocated_.insert(spec);

    free_spec(schema_[index]);

    cells_[index] = cell;
    schema_[index] = spec;
  }
  std::vector<TupleCellSpec *> schema()
  {
    return schema_;
  }

  RC merge(VTuple &other, VTuple &out)
  {
    size_t cell_num = cells_.size() + other.cell_num();
    out.schema_.resize(cell_num);
    out.cells_.resize(cell_num);

    auto schema_next = std::copy(schema_.begin(), schema_.end(), out.schema_.begin());
    auto cells_next = std::copy(cells_.begin(), cells_.end(), out.cells_.begin());
    std::copy(other.schema_.begin(), other.schema_.end(), schema_next);
    std::copy(other.cells_.begin(), other.cells_.end(), cells_next);
  }

private:
  void free_spec(TupleCellSpec *ptr){
    if (allocated_.count(ptr) > 0){
      allocated_.erase(ptr);
      delete ptr->expression_;
      delete ptr;
    }
  }
  std::vector<TupleCellSpec *> schema_;
  std::vector<TupleCell> cells_;
  // record the spec allocated by me
  std::set<TupleCellSpec *> allocated_;
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
