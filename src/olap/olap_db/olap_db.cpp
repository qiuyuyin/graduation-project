#include <vector>
#include <ctime>
#include <string>
#include <sstream>
#include <fstream>
#include <filesystem>

#include "olap_db/olap_db.h"

void OlapDB::init(std::string olap_path, std::string oltp_path)
{
  this->olap_path_ = olap_path;
  this->oltp_path_ = oltp_path;

  common::check_directory(olap_path);

  if (!common::is_directory(olap_path.c_str())) {
    return;
  }

  if (!common::is_directory(oltp_path.c_str())) {
    return;
  }

  clog_manager_ = new CLogManager(oltp_path.c_str());
  if (clog_manager_ == nullptr) {
    LOG_ERROR("Failed to init CLogManager.");
    return;
  }
  open_all_tables();
}

void OlapDB::open_all_tables()
{
  std::vector<std::string> table_meta_files;
  int ret = common::list_file(oltp_path_.c_str(), TABLE_META_FILE_PATTERN, table_meta_files);
  if (ret < 0) {
    LOG_ERROR("Failed to list table meta files under %s.", oltp_path_.c_str());
  }

  for (const std::string &filename : table_meta_files) {
    OlapTable *table = new OlapTable();
    table->open(filename.c_str(), oltp_path_.c_str(), olap_path_, clog_manager_);
    // if (rc != RC::SUCCESS) {
    //   delete table;
    //   LOG_ERROR("Failed to open table. filename=%s", filename.c_str());
    //   return rc;
    // }

    // if (opened_tables_.count(table->name()) != 0) {
    //   delete table;
    // }
    table->base_dir_ = oltp_path_;
    opened_tables_[table->name_] = table;
    // LOG_INFO("Open table: %s, file: %s", table->name(), filename.c_str());
  }
  //   LOG_INFO("All table have been opened. num=%d", opened_tables_.size());
}

OlapTable *OlapDB::find_table(const char *table_name) const
{
  std::unordered_map<std::string, OlapTable *>::const_iterator iter = opened_tables_.find(table_name);
  if (iter != opened_tables_.end()) {
    return iter->second;
  }
  return nullptr;
}

std::string OlapDB::select(std::string sql)
{
  ColumnList columns;
  columns.extractColumns(sql);
  OlapTable *table = find_table(columns.getTableName().c_str());
  if (table == nullptr) {
    return "not found table " + columns.getTableName();
  }
  auto str = table->select(columns.getColumns());
  return str;
}

void OlapDB::recover()
{
  clog_manager_->recover();
  CLogMTRManager *mtr_manager = clog_manager_->get_mtr_manager();
  for (auto it = mtr_manager->log_redo_list.begin(); it != mtr_manager->log_redo_list.end(); it++) {
    CLogRecord *clog_record = *it;
    if (clog_record->get_log_type() != CLogType::REDO_INSERT && clog_record->get_log_type() != CLogType::REDO_DELETE) {
      delete clog_record;
      continue;
    }

    auto find_iter = mtr_manager->trx_commited.find(clog_record->get_trx_id());
    if (find_iter == mtr_manager->trx_commited.end()) {
      delete clog_record;
    } else if (find_iter->second == false) {
      delete clog_record;
      continue;
    }

    if (this->trx_ >= clog_record->get_trx_id()) {
      delete clog_record;
      continue;
    }

    OlapTable *table = find_table(clog_record->log_record_.ins.table_name_);
    if (table == nullptr) {
      delete clog_record;
      continue;
    }

    if (!table->is_recovering_) {
      table->begin_recover();
    }

    auto table_meta = table->table_meta_;
    auto builder = table->builder_;
    switch (clog_record->get_log_type()) {
      case CLogType::REDO_INSERT: {
        char *record_data = new char[clog_record->log_record_.ins.data_len_];
        memcpy(record_data, clog_record->log_record_.ins.data_, clog_record->log_record_.ins.data_len_);
        const int sys_field_num = table_meta.sys_field_num();
        const int field_num = table_meta.field_num();
        int count = field_num - sys_field_num;
        std::vector<Value> values;
        for (int i = 0; i < field_num; i++) {
          const FieldMeta *field = table_meta.field(i);
          int len = field->len();
          char *curData = new char[len];
          memcpy(curData, record_data + field->offset(), len);
          values.push_back({field->type(), curData});
        }
        builder->push_row(values);
        delete[] record_data;
      } break;
      case CLogType::REDO_DELETE: {
        Record record;
        record.set_rid(clog_record->log_record_.del.rid_);
      } break;
      default: {
      }
    }

    this->trx_ = clog_record->get_trx_id();
    delete clog_record;
  }

  for (const auto &pair : this->opened_tables_) {
    if (pair.second->is_recovering_) {
      pair.second->end_recover();
    }
  }
  // delete clog_manager_;
  clog_manager_ = new CLogManager(this->oltp_path_.c_str());
  if (clog_manager_ == nullptr) {
    LOG_ERROR("Failed to init CLogManager.");
    return;
  }
}
