#include "olap_table/olap_table.h"

#include <vector>
#include <ctime>
#include <sstream>
#include <fstream>
#include <zstd.h>
// #include <string>
#include <filesystem>
#include <algorithm>

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
  auto curIndex = std::to_string(this->row_set_id_ + 1);
  common::check_directory(this->storage_dir_);
  rowset.flush(this->storage_dir_ + common::FILE_PATH_SPLIT_STR + curIndex);
  this->row_set_id_++;
  this->is_recovering_ = false;
}

void OlapTable::recover()
{}

void OlapTable::select(std::vector<std::string> cols)
{
  std::vector<int> col2index;

  for (int i = 0; i < cols.size(); i++) {
    int index = this->table_meta_.field_index(cols[i].c_str()) + this->table_meta_.sys_field_num();
    col2index.push_back(index);
  }
  for (int i = 0; i < col2index.size(); i++) {
    std::vector<Value> colValue;
    this->read_col(col2index[i], colValue);
    auto filed = this->table_meta_.field(i);
    for (int i = 0; i < colValue.size(); i++) {
      auto str = this->to_string(colValue[i], filed);
      std::cout << str << std::endl;
    }
  }
}

void OlapTable::select_sql(std::string sql)
{
  ColumnList* columns = ColumnList::extractColumns(sql);
}

void OlapTable::read_col(int col_index, std::vector<Value> &colValue)
{
  // 首先将数据从文件中读取出来，然后解压，然后读取数据
  std::vector<std::string> dirList;
  int rc = common::getDirList(dirList, this->storage_dir_, "^[0-9]+$");
  std::sort(dirList.begin(), dirList.end());

  for (int i = 0; i < dirList.size(); i++) {
    auto field = table_meta_.field(col_index);
    auto index = std::to_string(col_index + 1);
    auto filename = dirList[i] + "/" + index + ".col";
    std::ifstream file(filename, std::ios::binary);  // 打开文件

    file.seekg(0, std::ios::end);        // 将文件指针定位到文件末尾
    std::streamoff size = file.tellg();  // 获取文件大小
    size_t int_size = static_cast<size_t>(size);
    std::cout << "File size: " << size << " bytes" << std::endl;
    char buf[int_size] = {0};
    char *data = buf;
    // 从文件中读取出来data
    common::readFromFile(filename, data, int_size);
    // 将data解压
    ZSTD_DCtx *dctx = ZSTD_createDCtx();
    if (!dctx) {
      std::cerr << "Failed to create ZSTD decompression context." << std::endl;
    }

    // 获取解压缩后的数据大小
    const size_t decompressed_size = ZSTD_getFrameContentSize(data, int_size);
    if (decompressed_size == ZSTD_CONTENTSIZE_ERROR || decompressed_size == ZSTD_CONTENTSIZE_UNKNOWN) {
      std::cerr << "Failed to get decompressed size." << std::endl;
    }

    // 分配解压缩后的数据缓冲区
    char decompressed_data[decompressed_size];
    const size_t decompressed_bytes = ZSTD_decompressDCtx(dctx, decompressed_data, decompressed_size, data, int_size);
    if (ZSTD_isError(decompressed_bytes)) {
      std::cerr << "Failed to decompress data: " << ZSTD_getErrorName(decompressed_bytes) << std::endl;
    }
    for (int i = 0; i < decompressed_size / field->len(); i++) {
      Value value;
      value.type = field->type();
      char *putData = new char[field->len()];
      memcpy(putData, decompressed_data + i * field->len(), field->len());
      value.data = putData;
      colValue.push_back(value);
    }
    file.close();
  }
}

std::string OlapTable::to_string(Value &value, const FieldMeta *filed)
{
  std::stringstream os;
  auto data = value.data;
  auto attr_type_ = value.type;
  switch (attr_type_) {
    case INTS: {
      os << *(int *)data;
    } break;
    case FLOATS: {
      float v = *(float *)data;
      os << double2string(v);
    } break;
    case CHARS: {
      auto char_data = (char *)value.data;
      char str[filed->len()];
      strcpy(str, char_data);
      for (int i = 0; i < filed->len(); i++) {
        if (str[i] == '\0') {
          break;
        }
        os << str[i];
      }
    } break;
    case DATES: {
      Date v = *(Date *)data;
      os << std::setw(4) << std::setfill('0') << static_cast<int>(v.year) << '-' << std::setw(2) << std::setfill('0')
         << static_cast<int>(v.month) << '-' << std::setw(2) << std::setfill('0') << static_cast<int>(v.day);
    } break;
    default: {
      LOG_WARN("unsupported attr type: %d", attr_type_);
    } break;
  }
  return std::string(os.str());
}