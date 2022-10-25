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

static vector<QueryField> get_query_field(string sql) {
  auto parse = [](string temp){
    QueryField queryField;
    auto pos = temp.find("as");
    if (pos == temp.npos) {
      queryField.name = temp;
    } else {
      queryField.name = temp.substr(0, pos-1);
      queryField.alias = temp.substr(pos+3);
    }
    return queryField;
  };
  vector<QueryField> res;
  auto pos1 = sql.find("select"), pos2 = sql.find("from");
  if (pos1 == sql.npos || pos2 == sql.npos) {
    return res;
  }
  sql = sql.substr(pos1+7, pos2-1);
  if ((pos1 = sql.find(",")) == sql.npos) {
    res.push_back(parse(sql));
  } else {
    auto sql_list = split(sql, ",");
    for (auto s : sql_list) {
      res.push_back(parse(s));
    }
  }
  return res;
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
  const std::vector<TupleCellSpec> &query_fields() const { return query_fields_; }
  const std::vector<AggregateField> &aggregate_fields() const { return aggregate_fields_; }

  const std::vector<OrderByField> &orderby_fields() const {return orderby_fields_;}
  FilterStmt *filter_stmt() const { return filter_stmt_; }

private:
  //project operator
  std::vector<TupleCellSpec> query_fields_;
  //aggregate
  vector<AggregateField> aggregate_fields_;
  vector<TupleCellSpec> groupby_fields_;
  //predicate
  FilterStmt *filter_stmt_ = nullptr;
  //scan operator
  std::vector<Table *> tables_;
  //orderby
  vector<OrderByField> orderby_fields_;

  std::unordered_map<string, string> alias_map_;

};

