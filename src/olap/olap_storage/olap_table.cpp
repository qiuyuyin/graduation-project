#include "olap_storage/olap_table.h"
#include "olap_storage/data_chunk.h"
#include <vector>
#include <ctime>
#include <sstream>
#include <fstream>
#include <filesystem>

#include "common/defs.h"
#include "storage/common/table.h"
#include "storage/common/table_meta.h"
#include "common/log/log.h"
#include "common/lang/string.h"
#include "storage/clog/clog.h"

void OlapTable::open(const char *meta_file, const char *base_dir,CLogManager *clog_manager)
{
  this->clog_manager_ = clog_manager;
  TableMeta table_meta;
  std::fstream fs;
  std::string meta_file_path = std::string(base_dir) + common::FILE_PATH_SPLIT_STR + meta_file;
  fs.open(meta_file_path, std::ios_base::in | std::ios_base::binary);
  if (!fs.is_open()) {
    LOG_ERROR("Failed to open meta file for read. file name=%s, errmsg=%s", meta_file_path.c_str(), strerror(errno));
  }
  if (table_meta.deserialize(fs) < 0) {
    LOG_ERROR("Failed to deserialize table meta. file name=%s", meta_file_path.c_str());
    fs.close();
  }
  fs.close();
  this->name_ = table_meta.name();
  this->table_meta_ = table_meta;
}

void OlapTable::insert(std::vector<Value> values) {
    
}

void OlapTable::recover() {
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
    DataChunkBuilder builder(4);
    switch (clog_record->get_log_type()) {
      case CLogType::REDO_INSERT: {
        char *record_data = new char[clog_record->log_record_.ins.data_len_];
        memcpy(record_data, clog_record->log_record_.ins.data_, clog_record->log_record_.ins.data_len_);
        const int sys_field_num = table_meta_.sys_field_num();
        const int field_num = table_meta_.field_num();
        int count = field_num - sys_field_num;
        std::vector<Value> values;
        for (int i = 0; i < field_num; i++) {
          const FieldMeta *field = table_meta_.field(i);
          int len = field->len();
          char *curData = new char[len];
          memcpy(curData, record_data + field->offset(), len);
          values.push_back({field->type(), curData});
        }
        builder.push_row(values);
        delete[] record_data;
      } break;
      case CLogType::REDO_DELETE: {
        Record record;
        record.set_rid(clog_record->log_record_.del.rid_);
      } break;
      default: {
      }
    }
  }
}