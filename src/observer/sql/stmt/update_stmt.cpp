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

UpdateStmt::UpdateStmt(Table *table,  std::vector<UpdateField> &update_fields, FilterStmt *filter_stmt, int value_amount)
  : table_ (table), update_fields_(update_fields), filter_stmt_(filter_stmt),value_amount_(value_amount)
{}

UpdateStmt::~UpdateStmt()
{
  if (nullptr != filter_stmt_) {
    delete filter_stmt_;
    filter_stmt_ = nullptr;
  }
}

RC UpdateStmt::create(Db *db, Updates &update, Stmt *&stmt)
{
  // TODO
  const char *table_name = update.relation_name;
  if (nullptr == db || nullptr == table_name) {
    LOG_WARN("invalid argument. db=%p, table_name=%p", db, table_name);
    return RC::INVALID_ARGUMENT;
  }

  // check whether the table exists
  Table *table = db->find_table(table_name);
  if (nullptr == table) {
    LOG_WARN("no such table. db=%s, table_name=%s", db->name(), table_name);
    return RC::SCHEMA_TABLE_NOT_EXIST;
  }
  // check update fields
  std::vector<UpdateField> update_fields;
  for(size_t i = 0;i < update.update_num; i++) {
    UpdateRecord &update_record = update.update_records[i];
    const char *field_name = update_record.attribute_name;

    const FieldMeta *field_meta = table->table_meta().field(field_name);
    if (nullptr == field_meta) {
      LOG_WARN("no such field. field=%s.%s.%s", db->name(), table->name(), field_name);
      return RC::SCHEMA_FIELD_MISSING;
    }

    // check fields type
    const AttrType field_type = field_meta->type();
    AttrType value_type = update_record.value.type;

    if(field_type == TEXTS && value_type == CHARS) {
      update_record.value.type = TEXTS;
      value_type = TEXTS;
    }
    if (field_type != value_type) { // TODO try to convert the value type to field type
      LOG_WARN("field type mismatch. table=%s, field=%s, field type=%d, value_type=%d", 
                table_name, field_meta->name(), field_type, value_type);
      return RC::SCHEMA_FIELD_TYPE_MISMATCH;
    }

    update_fields.push_back(UpdateField(table, field_meta, &update_record.value));
  }

  // create filter statement in `where` statement
  FilterStmt *filter_stmt = nullptr;
  std::unordered_map<std::string, Table *> table_map{std::make_pair(table_name,table)};
  RC rc = FilterStmt::create(db, table, &table_map,
           update.conditions, update.condition_num, filter_stmt);
  if (rc != RC::SUCCESS) {
    LOG_WARN("cannot construct filter stmt");
    return rc;
  }

  // stmt = new UpdateStmt(table,update_field,&update.value,filter_stmt,1);
  // everything alright
  UpdateStmt *update_stmt = new UpdateStmt();
  update_stmt->table_ = table;
  update_stmt->update_fields_.swap(update_fields);
  update_stmt->filter_stmt_ = filter_stmt;
  update_stmt->value_amount_ = 1;
  stmt = update_stmt;

  return RC::SUCCESS;
}
