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

static void wildcard_fields(Table *table, std::vector<shared_ptr<TupleCellSpec>> &query_fields, bool multi_table)
{
  const TableMeta &table_meta = table->table_meta();
  const int field_num = table_meta.field_num();
  for (int i = table_meta.sys_field_num(); i < field_num; i++) {
    string name = table_meta.field(i)->name();
    if (multi_table) {
      name = string(table->name()) + "." + name;
    }
    auto expr = new VarExpr(name, table_meta.field(i)->type());
    auto tuple_cell_spec = make_shared<TupleCellSpec>(expr);
    query_fields.push_back(tuple_cell_spec);
  }
}

RC SelectStmt::create(Db *db, const string sql_string, const Selects &select_sql, Stmt *&stmt)
{
  if (nullptr == db) {
    LOG_WARN("invalid argument. db is null");
    return RC::INVALID_ARGUMENT;
  }


  //检测规则1 聚合和单个字段的混合测试语句如果没有groupby直接返回failure
  int agg_num = 0;
  for (int i = 0; i < select_sql.attr_num; ++i) {
    if (select_sql.attributes[i].aggregation_type != AggregationType::NO_Aggregation) {
      agg_num++;
    }
  }
  if (agg_num != select_sql.attr_num && select_sql.group_by.attr_num == 0) {
    return INVALID_ARGUMENT;
  }

  // collect tables in `from` statement
  vector<Table*> tables;
  unordered_map<std::string, Table*> table_map;
  unordered_map<string, string> alias_map;
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
    tables.insert(tables.begin(), table);
    if (select_sql.relations[i].alias != nullptr) {
      alias_map.insert(pair<string, string>(table_name, select_sql.relations[i].alias));
    }
    table_map.insert(std::pair<std::string, Table*>(table_name, table));
  }

  // 检查attribute里的列是否存在在表中
  for (int i = 0; i < select_sql.attr_num; ++i) {
    auto attr = select_sql.attributes[i];
    Table* table = nullptr;
    if (common::is_blank(attr.relation_name)) {
      table = tables[0];
      if (strcmp(attr.attribute_name, "*") == 0 || strcmp(attr.attribute_name, "1") == 0) {
        continue;
      }
    } else {
      table = table_map[attr.relation_name];
    }
    if (table->table_meta().field(attr.attribute_name) == nullptr) {
      LOG_WARN("the attribute name isn't in the tables' filed");
      return INVALID_ARGUMENT;
    }
  }

  // collect query fields in `select` statement
  // select * from
  vector<shared_ptr<TupleCellSpec>> query_fields;
  if (select_sql.attr_num == 1 && common::is_blank(select_sql.attributes[0].relation_name) && 0 == strcmp(select_sql.attributes[0].attribute_name, "*") && select_sql.attributes[0].aggregation_type == AggregationType::NO_Aggregation) {
    bool multi_table = (tables.size() > 1);
    for (auto table : tables) {
      wildcard_fields(table, query_fields, multi_table);
    }
  } else {
    vector<QueryField> parse_fields = get_query_field(sql_string, tables.size() > 1);
    for (int i = 0; i < parse_fields.size(); ++i) {
      auto parse_field = parse_fields[i];
      Expression* expr = nullptr;
      if (select_sql.expr_list.exprs[i].expr_cell_num > 1) {
        vector<string> expr_cells;
        for (int j = 0; j < select_sql.expr_list.exprs[i].expr_cell_num; ++j) {
          expr_cells.push_back(select_sql.expr_list.exprs[i].data[j]);
        }
        expr = new CalculateExpr(parse_field.name, expr_cells, AttrType::UNDEFINED);
      } else {
        expr = new VarExpr(parse_field.name, AttrType::UNDEFINED);
      }
      auto tuple_cell_spec = make_shared<TupleCellSpec>(expr);


      if (parse_field.alias != "") {
        tuple_cell_spec->set_alias(parse_field.alias.c_str());
      }
      query_fields.push_back(tuple_cell_spec);
    }
  }

  // collect aggregate fields in `select` statement
  unordered_set<string> name_set;
  vector<AggregateField> aggregate_fields;
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
    if (name_set.count(key) == 1) {
      continue;
    }
    name_set.insert(key);
    Expression* expr = new VarExpr(name, AttrType::UNDEFINED);
    auto tuple_cell_spec = make_shared<TupleCellSpec>(expr);
    AggregateField aggregate_field;
    aggregate_field.op_type = attribute.aggregation_type;
    aggregate_field.aggregate_field = tuple_cell_spec;
    aggregate_fields.push_back(aggregate_field);
  }

  // collect group by field
  vector<shared_ptr<TupleCellSpec>> groupby_fields;
  name_set.clear();
  for (int i = 0; i < select_sql.group_by.attr_num; ++i) {
    auto attr = select_sql.group_by.attributes[i];
    if (attr.attribute_name == nullptr) {
      return INVALID_ARGUMENT;
    }
    string name = attr.attribute_name;
    if (attr.relation_name != nullptr) {
      name = string(attr.relation_name) + "." + attr.attribute_name;
    }
    if (name_set.count(name) == 1) {
      continue;
    }
    name_set.insert(name);
    Expression* expr = nullptr;
    if (attr.relation_name == nullptr) {
      expr = new FieldExpr(tables[0], tables[0]->table_meta().field(attr.attribute_name));
    } else {
      expr = new FieldExpr(table_map[attr.relation_name], table_map[attr.relation_name]->table_meta().field(attr.attribute_name));
    }
    auto tuple_cell_spec = make_shared<TupleCellSpec>(expr);
    groupby_fields.push_back(tuple_cell_spec);
  }

  // collect orderby  in `select` statement
  vector<OrderByField> res_orderby_field;
  for(int i = select_sql.order_by.order_info_num -1 ; i>=0;i--){
    auto od_attr = select_sql.order_by.attrs[i];
    auto od_t = select_sql.order_by.od_types[i];
    string name ;
    if (od_attr.relation_name != nullptr) {
      name = string(od_attr.relation_name) + "." + od_attr.attribute_name;
    } else {
      name = od_attr.attribute_name;
    }
    Expression *expr = new VarExpr(name,AttrType::UNDEFINED);
    auto tupleCellSpec = make_shared<TupleCellSpec>(expr);
    OrderByField odb_field;
    odb_field.od_type = od_t;
    odb_field.orderby_field = tupleCellSpec;
    res_orderby_field.push_back(odb_field);
  }

  // collect condition from where, on, having
  FilterStmt *filter_stmt = nullptr;
  Condition* condition = new Condition[select_sql.condition_num + select_sql.group_by.having_condition_num];
  for (int i = 0; i < select_sql.condition_num; ++i) {
    condition[i] = select_sql.conditions[i];
  }
  for (int i = 0; i < select_sql.group_by.having_condition_num; ++i) {
    condition[select_sql.condition_num+i] = select_sql.group_by.having_condition[i];
  }
  int condition_num = select_sql.condition_num + select_sql.group_by.having_condition_num;
  RC rc = FilterStmt::create(db, tables[0], &table_map, condition, condition_num, filter_stmt);
  if (rc != RC::SUCCESS) {
    LOG_WARN("cannot construct filter stmt");
    return rc;
  }


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

//  // everything alright
  SelectStmt *select_stmt = new SelectStmt();
  select_stmt->query_fields_.swap(query_fields);
  select_stmt->aggregate_fields_.swap(aggregate_fields);
  select_stmt->groupby_fields_.swap(groupby_fields);
  select_stmt->tables_.swap(tables);
  select_stmt->alias_map_.swap(alias_map);
  select_stmt->filter_stmt_ = filter_stmt;
  select_stmt->orderby_fields_.swap(res_orderby_field);
  stmt = select_stmt;
  return RC::SUCCESS;
}
