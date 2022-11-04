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
// Created by Wangyunlai on 2022/6/5.
//

#pragma once

#include <vector>
#include <string>
#include "rc.h"
#include "sql/stmt/stmt.h"
#include "storage/common/field.h"
#include "sql/operator/aggregate_operator.h"
#include "sql/operator/sort_operator.h"
#include <unordered_map>
#include <unordered_set>
#include "util/util.h"

class FieldMeta;
class FilterStmt;
class Db;
class Table;
class TupleCellSpec;

using namespace std;

class QueryField {
public:
  string name;
  string alias;
};

static vector<QueryField> get_query_field(string sql, bool multi_table) {
  str_replace_by_regex(sql, " [Aa][Ss] ", " as ");
  str_replace_by_regex(sql, "[Ss][Ee][Ll][Ee][Cc][Tt] ", "select ");
  str_replace_by_regex(sql, " [Ff][Rr][Oo][Mm] ", " from ");

  auto parse = [](string temp, bool multi_table){
    QueryField queryField;
    temp = trim(temp);
    if (temp.find(" as ") == temp.npos) {
      str_replace_by_regex(temp, " ", " as ");
    }
    auto pos = temp.find(" as ");
    if (pos == temp.npos) {
      string name = trim(temp);
      if (name.find(".") != name.npos && !multi_table) {
        name = name.substr(name.find(".")+1, name.npos);
      }
      queryField.name = name;
    } else {
      queryField.name = trim(temp.substr(0, pos));
      queryField.alias = trim(temp.substr(pos+4, temp.length()-pos-4));
    }
    return queryField;
  };
  vector<QueryField> res;
  auto pos1 = sql.find("select"), pos2 = sql.find("from");
  if (pos1 == sql.npos || pos2 == sql.npos) {
    return res;
  }
  sql = sql.substr(pos1+7, pos2-pos1-8);
  if ((pos1 = sql.find(",")) == sql.npos) {
    res.push_back(parse(sql, multi_table));
  } else {
    auto sql_list = split(sql, ",");
    for (auto s : sql_list) {
      res.push_back(parse(s, multi_table));
    }
  }
  return res;
}

static void append_agg_field_by_condition(Condition &condition, vector<AggregateField>& agg_fields, unordered_set<string>& excludes_set) {
  auto build = [&](Expr& expr){
    for (int i = 0; i < expr.expr_cell_num; ++i) {
      string e = expr.data[i];
      if (e.find("(") != e.npos && e.find(")") != e.npos) {
        auto left_index = e.find("("), right_index = e.find(")");
        string name = e.substr(left_index+1, right_index-left_index-1);
        string agg_name = e.substr(0, left_index);
        string key = agg_name + "(" + name + ")";
        if (excludes_set.count(key) == 1) {
          continue;
        }
        excludes_set.insert(key);
        auto type = string_to_aggregate_type(agg_name.c_str());
        Expression* expr = new VarExpr(name, AttrType::UNDEFINED);
        auto tuple_cell_spec = make_shared<TupleCellSpec>(expr);
        AggregateField aggregate_field;
        aggregate_field.op_type = type;
        aggregate_field.aggregate_field = tuple_cell_spec;
        agg_fields.push_back(aggregate_field);
      }
    }
  };
  if (condition.left_type == 3)  {
    build(condition.left_expr);
  }
  if (condition.right_type == 3) {
    build(condition.right_expr);
  }
}


class SelectStmt : public Stmt
{
public:

  SelectStmt() = default;
  ~SelectStmt() override;

  StmtType type() const override { return StmtType::SELECT; }
public:
  static RC create(Db *db, const string sql_string, const Selects &select_sql, Stmt *&stmt);

public:
  const std::vector<Table *> &tables() const { return tables_; }
  const std::unordered_map<string, string>& alias_map() const { return alias_map_; }
  const std::vector<shared_ptr<TupleCellSpec>> &query_fields() const { return query_fields_; }
  const std::vector<AggregateField> &aggregate_fields() const { return aggregate_fields_; }
  const std::vector<shared_ptr<TupleCellSpec>> &groupby_fields() const { return groupby_fields_; }
  const std::vector<OrderByField> &orderby_fields() const {return orderby_fields_;}
  FilterStmt *filter_stmt() const { return filter_stmt_; }

private:
  //project operator
  std::vector<shared_ptr<TupleCellSpec>> query_fields_;
  //aggregate
  vector<AggregateField> aggregate_fields_;
  vector<shared_ptr<TupleCellSpec>> groupby_fields_;
  //predicate
  FilterStmt *filter_stmt_ = nullptr;
  //scan operator
  std::vector<Table*> tables_;
  //orderby
  vector<OrderByField> orderby_fields_;

  std::unordered_map<string, string> alias_map_;

};

