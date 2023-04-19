#include "olap_storage/olap_table.h"
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
#include "common/os/path.h"
#include "common/io/io.h"


void OlapTable::open(const char *meta_file, const char *base_dir, std::string storage_dir, CLogManager *clog_manager)
{
  this->clog_manager_ = clog_manager;
  this->storage_dir_ = storage_dir;
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
  this->storage_dir_ = storage_dir + common::FILE_PATH_SPLIT_STR + this->name_;
  // find current row_set_id_
  if (!common::is_directory(storage_dir_.c_str())) {
      return;
  }
  std::vector<std::string> dirList;
  int rc = common::getDirList(dirList, this->storage_dir_, "^[0-9]+$");
  this->row_set_id_ = dirList.size();
}

void OlapTable::insert(std::vector<Value> values)
{
  this->builder_->push_row(values);
}

void OlapTable::begin_recover()
{
  this->builder_ = new DataChunkBuilder(this->table_meta_.field_num());
  this->is_recovering_ = true;
}

void OlapTable::end_recover()
{
  if (!is_recovering_) {
    return;
  }
  std::vector<FieldMeta> fields = this->table_meta_.fields_;
  size_t num = table_meta_.field_num();
  StorageMemRowset rowset(num, fields);
  auto chunk = builder_->take();
  rowset.append(*chunk);
  auto curIndex = std::to_string(this->row_set_id_+1);
  common::check_directory(this->storage_dir_ );
  rowset.flush(this->storage_dir_ + common::FILE_PATH_SPLIT_STR + curIndex);
  this->row_set_id_++;
  this->is_recovering_ = false;
}

void OlapTable::recover()
{}