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
#include "util/util.h"

class Table;
class VTuple;
enum class TupleType {
  UNKNOWN,
  V,
  ROW,
};
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
    this->alias_ = strdup(alias);
  }
  const char *alias() const
  {
    return alias_;
  }

  Expression *expression() const
  {
    return expression_;
  }

  std::string table_name() const
  {
    if (expression_ == nullptr) {
      return "";
    }
    switch (expression_->type()) {
      case ExprType::FIELD: {
        auto expr = static_cast<FieldExpr *>(expression_);
        return expr->table_name();
      }
      default:
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
      default: {
        // todo
        return AttrType ::UNDEFINED;
      }
    }
  }

  std::string expr_name() const
  {
    return expression_->get_name();
  }

private:
  const char *alias_ = nullptr;
  Expression *expression_ = nullptr;
};

class Tuple {
public:
  Tuple() = default;
  virtual ~Tuple() = default;

  virtual TupleType get_tuple_type() const = 0;
  virtual int cell_num() const = 0;
  virtual RC cell_at(int index, TupleCell &cell) const = 0;
  virtual RC find_cell(const Field &field, TupleCell &cell) const = 0;

  virtual RC cell_spec_at(int index, std::shared_ptr<TupleCellSpec> &spec) const = 0;
};

class RowTuple : public Tuple {
public:
  RowTuple() = default;
  virtual ~RowTuple()
  {
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
      speces_.push_back(std::make_shared<TupleCellSpec>(new FieldExpr(table, &field)));
    }
  }

  TupleType get_tuple_type() const override
  {
    return TupleType::ROW;
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
    auto spec = speces_[index];
    FieldExpr *field_expr = (FieldExpr *)spec->expression();
    const FieldMeta *field_meta = field_expr->field().meta();
    int value_null_map = *(int *)(this->record_->data() + field_expr->field().table()->table_meta().field(1)->offset());
    bool is_null = index >= table_->table_meta().sys_field_num() &&
                   has_bit_set(value_null_map, index - table_->table_meta().sys_field_num());
    if (is_null) {
      cell.set_is_null(true);
    } else {
      cell.set_data(this->record_->data() + field_meta->offset());
    }

    cell.set_type(field_meta->type());
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

  RC cell_spec_at(int index, std::shared_ptr<TupleCellSpec> &spec) const override
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
  std::vector<std::shared_ptr<TupleCellSpec>> speces_;
};

class VTuple : public Tuple {
public:
  VTuple() = default;
  VTuple(size_t size)
  {
    schema_.resize(size);
    cells_.resize(size);
  }
  VTuple(const RowTuple &row_tuple)
  {
    clear();
    append_row_tuple(row_tuple);
  }
  VTuple(const Tuple &tuple)
  {
    clear();
    switch (tuple.get_tuple_type()) {
      case TupleType::V: {
        merge(dynamic_cast<const VTuple &>(tuple), *this);
      } break;
      case TupleType::ROW: {
        append_row_tuple((const RowTuple &)tuple);
      } break;
      case TupleType::UNKNOWN: {
        abort();
      }
    }
  }
  VTuple &operator=(const VTuple &other)
  {
    clear();
    merge(other, *this);
    return *this;
  }
  VTuple &operator=(const RowTuple &other)
  {
    clear();
    append_row_tuple(other);
    return *this;
  }
  ~VTuple()
  {
    schema_.clear();
  }
  void clear()
  {
    this->schema_.clear();
    this->cells_.clear();
    this->name_to_idx_.clear();
  }
  int cell_num() const override
  {
    return schema_.size();
  }

  TupleType get_tuple_type() const override
  {
    return TupleType::V;
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
    auto full_name = get_full_name(&field);
    return get_cell_by_full_name(full_name, cell);
  }

  RC find_cell(const TupleCellSpec &spec, TupleCell &cell) const
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
      case ExprType::VAR: {
        string name = spec.expr_name();
        return get_cell_by_expr_name(name, cell);
      }
      case ExprType::CALCULATE: {
        auto expr = static_cast<CalculateExpr *>(spec.expression());
        return expr->get_value(*this, cell);
      }
      default:
        return RC::UNIMPLENMENT;
    }
  }
  RC cell_spec_at(int index, shared_ptr<TupleCellSpec> &spec) const override
  {
    if (index < 0 || index >= static_cast<int>(schema_.size())) {
      LOG_WARN("invalid argument. index=%d", index);
      return RC::INVALID_ARGUMENT;
    }
    spec = schema_[index];
    return RC::SUCCESS;
  };
  void append_cell(TupleCell &cell, const shared_ptr<TupleCellSpec> &spec)
  {
    cells_.push_back(cell);
    schema_.push_back(spec);
    if (spec->expression_->type() != ExprType::VALUE) {
      std::string full_name = get_full_name(spec);
      name_to_idx_[full_name] = cells_.size() - 1;
    }
  }
  RC append_row_tuple(const RowTuple &row)
  {
    int cells = row.cell_num();
    for (int i = 0; i < cells; i++) {
      TupleCell cell;
      std::shared_ptr<TupleCellSpec> spec;
      row.cell_at(i, cell);
      row.cell_spec_at(i, spec);
      append_cell(cell, spec);
    }
    return SUCCESS;
  }
  RC append_value(Value &value)
  {
    auto expr = new ValueExpr(value);
    auto spec = std::make_shared<TupleCellSpec>(expr);
    TupleCell cell;

    expr->get_tuple_cell(cell);
    append_cell(cell, spec);
    return RC::SUCCESS;
  }
  RC append_var(std::string name, AttrType type, int length, void *data, bool is_cell_null)
  {
    TupleCell cell(type, static_cast<char *>(data));
    cell.set_is_null(is_cell_null);
    cell.set_length(length);
    auto expr = new VarExpr(name, type);
    auto spec = make_shared<TupleCellSpec>(expr);

    cells_.push_back(cell);
    schema_.push_back(spec);
    return RC::SUCCESS;
  }
  RC set_schema(std::vector<std::shared_ptr<TupleCellSpec>> schema)
  {
    schema_ = schema;
    cells_.resize(schema.size());
    return RC::SUCCESS;
  }
  RC set_field(int index, TupleCell &cell, std::shared_ptr<TupleCellSpec> spec)
  {
    if (index < 0 || index >= static_cast<int>(schema_.size())) {
      LOG_WARN("invalid argument. index=%d", index);
      return RC::INVALID_ARGUMENT;
    }

    std::string col_name = get_full_name(spec);
    cells_[index] = cell;
    name_to_idx_[col_name] = index;
    return RC::SUCCESS;
  }
  RC set_value(int index, Value &value)
  {
    auto expr = new ValueExpr(value);
    auto spec = std::make_shared<TupleCellSpec>(expr);
    TupleCell cell;

    expr->get_tuple_cell(cell);

    cells_[index] = cell;
    schema_[index] = spec;
    return RC::SUCCESS;
  }
  RC get_tuple_by_table_and_name(std::string table, std::string col_name, TupleCell &cell)
  {
    // TODO: replace "." with marco
    std::string full_name = table + "." + col_name;
    return get_cell_by_full_name(full_name, cell);
  }
  RC get_cell_by_full_name(std::string full_name, TupleCell &out) const
  {
    if (name_to_idx_.count(full_name) == 0) {
      LOG_WARN("field does not exist.");
      return RC::SCHEMA_FIELD_NOT_EXIST;
    }
    auto it = name_to_idx_.find(full_name);
    auto idx = it->second;
    out = cells_[idx];
    return RC::SUCCESS;
  }

  RC get_cell_by_expr_name(std::string col_name, TupleCell &out) const
  {
    for (int i = 0; i < schema_.size(); ++i) {
      if (schema_[i]->expr_name() == col_name) {
        cell_at(i, out);
        return SUCCESS;
      }
      if (schema_[i]->expression_->type() == ExprType::FIELD) {
        auto field_expr = (FieldExpr*)schema_[i]->expression_;
        if (col_name == string(field_expr->field().table_name()) + "." + field_expr->field().field_name()) {
          cell_at(i, out);
          return SUCCESS;
        }
      }
      if (schema_[i]->expr_name().find(".") != schema_[i]->expr_name().npos) {
        auto begin = schema_[i]->expr_name().find(".");
        auto field_name = schema_[i]->expr_name().substr(begin+1, schema_[i]->expr_name().npos);
        if (field_name == col_name) {
          cell_at(i, out);
          return SUCCESS;
        }
      }
    }
    return NOTFOUND;
  }
  std::vector<std::shared_ptr<TupleCellSpec>> schema()
  {
    return schema_;
  }

  // if &other == &out; the behaviour is undefined
  RC merge(const VTuple &other, VTuple &out)
  {
    size_t total_cell_num = cells_.size() + other.cell_num();
    auto left = this;
    auto right = &other;
    auto left_sz = left->cells_.size();

    out.schema_.resize(total_cell_num);
    out.cells_.resize(total_cell_num);
    auto schema_next = &out == left ? out.schema_.begin()
                                    : (std::copy(left->schema_.begin(), left->schema_.end(), out.schema_.begin()));
    auto cells_next =
        &out == left ? out.cells_.begin() : (std::copy(left->cells_.begin(), left->cells_.end(), out.cells_.begin()));

    std::copy(right->schema_.begin(), right->schema_.end(), schema_next);
    std::copy(right->cells_.begin(), right->cells_.end(), cells_next);

    // right
    out.name_to_idx_ = left->name_to_idx_;
    for (int i = left_sz; i < total_cell_num; i++) {
      auto spec = right->schema_[i - left_sz];
      auto full_name = get_full_name(spec);
      out.name_to_idx_[full_name] = i;
    }
    return RC::SUCCESS;
  }

private:
  std::string get_full_name(const shared_ptr<TupleCellSpec> spec) const
  {
    return spec == nullptr ? "" : spec->table_name() + "." + spec->expr_name();
  }

  std::string get_full_name(const TupleCellSpec *spec) const
  {
    return spec == nullptr ? "" : spec->table_name() + "." + spec->expr_name();
  }
  std::string get_full_name(const Field *field) const
  {
    return field == nullptr ? "" : (std::string(field->table_name()) + "." + field->field_name());
  }
  std::vector<std::shared_ptr<TupleCellSpec>> schema_;
  std::vector<TupleCell> cells_;
  std::map<std::string, size_t> name_to_idx_;
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
    speces_.clear();
  }

  void set_tuple(Tuple *tuple)
  {
    this->tuple_ = tuple;
  }

  void add_cell_spec(std::shared_ptr<TupleCellSpec> spec)
  {
    speces_.push_back(spec);
  }

  TupleType get_tuple_type() const override
  {
    return TupleType::UNKNOWN;
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

    auto spec = speces_[index];
    return spec->expression()->get_value(*tuple_, cell);
  }

  RC find_cell(const Field &field, TupleCell &cell) const override
  {
    return tuple_->find_cell(field, cell);
  }
  RC cell_spec_at(int index, std::shared_ptr<TupleCellSpec> &spec) const override
  {
    if (index < 0 || index >= static_cast<int>(speces_.size())) {
      return RC::NOTFOUND;
    }
    spec = speces_[index];
    return RC::SUCCESS;
  }

private:
  std::vector<std::shared_ptr<TupleCellSpec>> speces_;
  Tuple *tuple_ = nullptr;
};
