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

#include "sql/stmt/update_stmt.h"
#include "common/log/log.h"
#include "storage/common/db.h"
#include "storage/common/table.h"
#include "filter_stmt.h"

UpdateStmt::UpdateStmt(Table *table, const char *update_attr, const Value *values, int value_amount)
    : table_(table), update_attr_(update_attr), values_(values), value_amount_(value_amount) {
}
RC UpdateStmt::create(Db *db, const Updates &update, Stmt *&stmt)
{
  const char *table_name = update.relation_name;

  // check whether the db and table input are valid
  if (nullptr == db || nullptr == table_name) {
    LOG_WARN("Invalid argument. Db = %s, table_name = %s",db->name(), table_name);
    return INVALID_ARGUMENT;
  }

  // check whether the table exists
  Table *table = db->find_table(table_name);
  if (nullptr == table) {
    LOG_WARN("No such table. Db = %s, table_name = %s", db->name(), table_name);
    return SCHEMA_TABLE_NOT_EXIST;
  }

  // check update field
  const TableMeta &table_meta = table->table_meta();
  const FieldMeta *filed_meta = table_meta.field(update.attribute_name);
  if(filed_meta == nullptr){
    LOG_WARN("The update attr[%s] doesn't exist",update.attribute_name);
    return SCHEMA_FIELD_NOT_EXIST;
  }
  if(filed_meta->type()!=update.value.type){
    LOG_WARN("The update attr[%s]'s type mismatches with filed meta's",update.attribute_name);
    return SCHEMA_FIELD_TYPE_MISMATCH;
  }

  // filter
  FilterStmt * filter_stmt = nullptr;
  std::unordered_map<std::string,Table *> table_map;
  table_map.insert(std::pair<std::string,Table *>(table_name,table));
  RC rc = FilterStmt::create(db,table,&table_map,update.conditions,update.condition_num,filter_stmt);
  if (rc!=RC::SUCCESS){
    LOG_WARN("Can't construct filter stmt");
    return rc;
  }

  UpdateStmt * update_stmt = new UpdateStmt(table,update.attribute_name,&update.value,1);
  update_stmt->filter_stmt_ = filter_stmt;
  stmt = update_stmt;
  return SUCCESS;
}
