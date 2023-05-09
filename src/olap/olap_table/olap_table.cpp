#include "olap_table/olap_table.h"

#include <string>
#include <vector>
#include <ctime>
#include <sstream>
#include <fstream>
#include <zstd.h>
#include <init.h>
#include <unordered_set>
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
  // 判断是否compact
  if (this->row_set_id_ > 2) {
    this->compact();
  }
}

void OlapTable::compact()
{
  auto num = this->table_meta_.field_num();
  vector<std::string> cols;
  std::unordered_set<int> id_set;
  std::unordered_set<int> no_display_set;
  // 将已经删除的id写入到集合中
  for (int i = 0; i < this->delete_list.size(); i++) {
    id_set.insert(this->delete_list[i]);
  }
  for (int i = 0; i < this->table_meta_.fields_.size(); i++) {
    cols.push_back(this->table_meta_.fields_[i].name());
  }
  auto it = std::find(cols.begin(), cols.end(), "id");
  int id_index;
  if (it != cols.end()) {
    // 使用std::distance函数计算指定元素的索引
    id_index = std::distance(cols.begin(), it);
  } else {
    return;
  }
  std::vector<std::vector<Value>> vals;
  for (int i = 0; i < num; i++) {
    std::vector<Value> colValue;
    this->read_col(i, colValue);
    vals.push_back(colValue);
    if (i == id_index) {
      for (int j = colValue.size() - 1; j >= 0; j--) {
        int _id = *(int *)colValue[j].data;
        auto it = id_set.find(_id);
        if (it != id_set.end()) {
          // 代表集合中存在，则不显示，将行号加入到set中
          no_display_set.insert(j);
        } else {
          id_set.insert(_id);
        }
      }
    }
  }
  // 删除指定数列的数据
  for (auto &row : vals) {
    std::vector<Value> new_row;
    for (int i = 0; i < row.size(); i++) {
      if (no_display_set.count(i) == 0) {
        new_row.push_back(row[i]);
      }
    }
    row = new_row;
  }
  // 先删除之前的所有rowset
  // 得到所有数据之后将数据重新写入到rowset中
  for (int i = 2; i < vals.size(); i++) {
    auto field = this->table_meta_.field(i);
    std::cout << field->name() << " | ";
    for (auto data : vals[i]) {
      auto str = this->to_string(data, field);
      std::cout << str << " | ";
    }
    std::cout << std::endl;
  }
  this->builder_ = new DataChunkBuilder(this->table_meta_.field_num());
  common::delete_directory(this->storage_dir_);

  common::check_directory(this->storage_dir_);
  std::vector<std::vector<Value>> transposed(vals[0].size(), std::vector<Value>(vals.size()));
  for (int i = 0; i < vals.size(); i++) {
    for (int j = 0; j < vals[i].size(); j++) {
      transposed[j][i] = vals[i][j];
    }
  }
  for (auto row : transposed) {
    this->builder_->push_row(row);
  }
  std::vector<FieldMeta> fields = this->table_meta_.fields_;
  StorageMemRowset rowset(num, fields);
  auto chunk = builder_->take();
  rowset.append(*chunk);
  auto curIndex = std::to_string(1);
  rowset.flush(this->storage_dir_ + common::FILE_PATH_SPLIT_STR + curIndex);
  this->row_set_id_ = 1;
  this->delete_list.clear();
}

void OlapTable::recover()
{}

std::string OlapTable::select(std::vector<std::string> cols)
{
  std::vector<int> col2index;
  std::unordered_set<int> id_set;
  std::unordered_set<int> no_display_set;
  // 将已经删除的id写入到集合中
  for (int i = 0; i < this->delete_list.size(); i++) {
    id_set.insert(this->delete_list[i]);
  }
  auto it = std::find(cols.begin(), cols.end(), "id");
  int id_index;
  if (it != cols.end()) {
    // 使用std::distance函数计算指定元素的索引
    id_index = std::distance(cols.begin(), it);
  } else {
    return "need id col";
  }

  for (int i = 0; i < cols.size(); i++) {
    int index = this->table_meta_.field_index(cols[i].c_str());
    if (index == -1) {
      return "not fount col ' " + cols[i] + " '";
    }
    index += this->table_meta_.sys_field_num();
    col2index.push_back(index);
  }
  std::stringstream ss;
  for (int i = 0; i < col2index.size(); i++) {
    auto field = this->table_meta_.field(col2index[i]);
    ss << field->name();
    if (i < col2index.size() - 1) {
      ss << " | ";
    }
  }
  ss << "\n";
  auto num = col2index.size();
  std::vector<std::vector<std::string>> vals;
  for (int i = 0; i < num; i++) {
    std::vector<Value> colValue;
    std::vector<std::string> colStr;
    this->read_col(col2index[i], colValue);
    auto filed = this->table_meta_.field(col2index[i]);
    for (int j = colValue.size() - 1; j >= 0; j--) {
      if (i == id_index) {
        int _id = *(int *)colValue[j].data;
        auto it = id_set.find(_id);
        if (it != id_set.end()) {
          // 代表集合中存在，则不显示，将行号加入到set中
          no_display_set.insert(j);
        } else {
          id_set.insert(_id);
        }
      }
      auto str = this->to_string(colValue[j], filed);
      std::cout << str << std::endl;
      colStr.push_back(str);
    }
    vals.push_back(colStr);
  }
  if (vals.size() > 0) {
    // i 行 j 列
    for (int i = vals[0].size() - 1; i >= 0; i--) {
      auto it = no_display_set.find(vals[0].size() - i - 1);
      if (it != no_display_set.end()) {
        // 代表集合中存在，则不显示
        continue;
      }
      for (int j = 0; j < vals.size(); j++) {
        ss << vals[j][i];
        if (j < vals.size() - 1) {
          ss << " | ";
        }
      }
      ss << "\n";
    }
  }
  return ss.str();
}

void OlapTable::select_sql(std::string sql)
{}

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
    const int array_size = int_size;
    // char buf[array_size] = {0};
    char *data = new char[array_size];
    // 从文件中读取出来data
    common::readFromFile(filename, data, int_size);

    int all_szie;
    char *all_data;
    if (compress_algo == "zstd") {
      // 将data解压
      ZSTD_DCtx *dctx = ZSTD_createDCtx();
      // 获取解压缩后的数据大小
      const size_t decompressed_size = ZSTD_getFrameContentSize(data, int_size);
      // 分配解压缩后的数据缓冲区
      char decompressed_data[decompressed_size];
      ZSTD_decompressDCtx(dctx, decompressed_data, decompressed_size, data, int_size);
      all_szie = decompressed_size;
      all_data = decompressed_data;
    } else {
      // 没有进行压缩
      all_szie = int_size;
      all_data = data;
    }

    for (int i = 0; i < all_szie / field->len(); i++) {
      Value value;
      value.type = field->type();
      char *putData = new char[field->len()];
      memcpy(putData, all_data + i * field->len(), field->len());
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