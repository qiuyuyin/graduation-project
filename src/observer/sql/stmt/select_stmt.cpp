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
// Created by Wangyunlai on 2022/6/6.
//

#include "sql/stmt/select_stmt.h"
#include "sql/stmt/filter_stmt.h"
#include "common/log/log.h"
#include "common/lang/string.h"
#include "storage/common/db.h"
#include "storage/common/table.h"
#include "sql/parser/parse.h"
#include "unordered_set"
#include <algorithm>

using namespace std;

SelectStmt::~SelectStmt()
{
  if (nullptr != filter_stmt_) {
    delete filter_stmt_;
    filter_stmt_ = nullptr;
  }
}

static void wildcard_fields(Table *table, std::vector<Field> &field_metas)
{
  const TableMeta &table_meta = table->table_meta();
  const int field_num = table_meta.field_num();
  for (int i = table_meta.sys_field_num(); i < field_num; i++) {
    field_metas.push_back(Field(table, table_meta.field(i)));
  }
}

RC SelectStmt::create(Db *db, const string sql_string, const Selects &select_sql, Stmt *&stmt)
{
  if (nullptr == db) {
    LOG_WARN("invalid argument. db is null");
    return RC::INVALID_ARGUMENT;
  }

  // collect tables in `from` statement
  std::vector<Table *> tables;
  std::unordered_map<std::string, Table *> table_map;
  for (size_t i = 0; i < select_sql.relation_num; i++) {
    const char *table_name = select_sql.relations[i].name;
    if (nullptr == table_name) {
      LOG_WARN("invalid argument. relation name is null. index=%d", i);
      return RC::INVALID_ARGUMENT;
    }

    Table *table = db->find_table(table_name);
    if (nullptr == table) {
      LOG_WARN("no such table. db=%s, table_name=%s", db->name(), table_name);
      return RC::SCHEMA_TABLE_NOT_EXIST;
    }

    tables.push_back(table);
    table_map.insert(std::pair<std::string, Table*>(table_name, table));
  }
  
  // collect query fields in `select` statement
  //todo 这里要考虑select*的情况
  vector<QueryField> query_fields = get_query_field(sql_string);
  vector<TupleCellSpec> res_query_fields;
  for (auto query_field : query_fields) {
      Expression* expr = new VarExpr(query_field.name, AttrType::UNDEFINED);
      TupleCellSpec* tupleCellSpec = new TupleCellSpec(expr);
      if (query_field.alias != "") {
        tupleCellSpec->set_alias(query_field.alias.c_str());
      }
      res_query_fields.push_back(*tupleCellSpec);
  }

  // collect aggregate fields in `select` statement
  unordered_set<string> aggregate_field_name_set;
  vector<AggregateField> res_aggregate_field;
  for (int i = 0; i < select_sql.attr_num; ++i) {
    auto attribute = select_sql.attributes[i];
    if (attribute.aggregation_type == AggregationType::NO_Aggregation) {
      continue;
    }
    string key, name;
    if (attribute.relation_name != nullptr) {
      name = string(attribute.relation_name) + "." + attribute.attribute_name;
      key = string(aggregate_type_to_string(attribute.aggregation_type)) + "(" + name + ")";
    } else {
      name = attribute.attribute_name;
      key = string(aggregate_type_to_string(attribute.aggregation_type)) + "(" + name + ")";
    }
    if (aggregate_field_name_set.count(key) == 1) {
      continue;
    }
    Expression* expr = new VarExpr(name, AttrType::UNDEFINED);
    TupleCellSpec* tupleCellSpec = new TupleCellSpec(expr);
    AggregateField aggregate_field;
    aggregate_field.op_type = attribute.aggregation_type;
    aggregate_field.aggregate_field = *tupleCellSpec;
    res_aggregate_field.push_back(aggregate_field);
  }




//  for (int i = select_sql.attr_num - 1; i >= 0; i--) {
//    const RelAttr &relation_attr = select_sql.attributes[i];
//
//    if (common::is_blank(relation_attr.relation_name) && 0 == strcmp(relation_attr.attribute_name, "*")) {
//      for (Table *table : tables) {
//        wildcard_fields(table, query_fields);
//      }
//
//    } else if (!common::is_blank(relation_attr.relation_name)) { // TODO
//      const char *table_name = relation_attr.relation_name;
//      const char *field_name = relation_attr.attribute_name;
//
//      if (0 == strcmp(table_name, "*")) {
//        if (0 != strcmp(field_name, "*")) {
//          LOG_WARN("invalid field name while table is *. attr=%s", field_name);
//          return RC::SCHEMA_FIELD_MISSING;
//        }
//        for (Table *table : tables) {
//          wildcard_fields(table, query_fields);
//        }
//      } else {
//        auto iter = table_map.find(table_name);
//        if (iter == table_map.end()) {
//          LOG_WARN("no such table in from list: %s", table_name);
//          return RC::SCHEMA_FIELD_MISSING;
//        }
//
//        Table *table = iter->second;
//        if (0 == strcmp(field_name, "*")) {
//          wildcard_fields(table, query_fields);
//        } else {
//          const FieldMeta *field_meta = table->table_meta().field(field_name);
//          if (nullptr == field_meta) {
//            LOG_WARN("no such field. field=%s.%s.%s", db->name(), table->name(), field_name);
//            return RC::SCHEMA_FIELD_MISSING;
//          }
//
//          query_fields.push_back(Field(table, field_meta));
//        }
//      }
//    } else {
//      if (tables.size() != 1) {
//        LOG_WARN("invalid. I do not know the attr's table. attr=%s", relation_attr.attribute_name);
//        return RC::SCHEMA_FIELD_MISSING;
//      }
//
//      Table *table = tables[0];
//      const FieldMeta *field_meta = table->table_meta().field(relation_attr.attribute_name);
//      if (nullptr == field_meta) {
//        LOG_WARN("no such field. field=%s.%s.%s", db->name(), table->name(), relation_attr.attribute_name);
//        return RC::SCHEMA_FIELD_MISSING;
//      }
//
//      query_fields.push_back(Field(table, field_meta));
//    }
//  }

  // create filter statement in `where` statement
//  FilterStmt *filter_stmt = nullptr;
//  RC rc = FilterStmt::create(db, default_table, &table_map,
//           select_sql.conditions, select_sql.condition_num, filter_stmt);
//  if (rc != RC::SUCCESS) {
//    LOG_WARN("cannot construct filter stmt");
//    return rc;
//  }
//
//  // 如果table的数量超过1，则交换顺序
//  if (tables.size() > 1) {
//    std::reverse(tables.begin(), tables.end());
//    vector<vector<Field>> swap_query_fields(tables.size());
//    for (auto field : query_fields) {
//      for (int i = 0; i < tables.size(); ++i) {
//        if (strcmp(tables[i]->name(), field.table_name()) == 0) {
//          swap_query_fields[i].push_back(field);
//        }
//      }
//    }
//    vector<Field> res;
//    for (auto temp : swap_query_fields) {
//      res.insert(res.end(), temp.begin(), temp.end());
//    }
//    query_fields = res;
//  }
//
//  // everything alright
//  SelectStmt *select_stmt = new SelectStmt();
//  select_stmt->tables_.swap(tables);
//  select_stmt->filter_stmt_ = filter_stmt;
//  stmt = select_stmt;
  return RC::SUCCESS;
}
