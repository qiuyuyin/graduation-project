// 在列存初始化的时候会读取行存中已经存在的table元数据，包含有每个列的属性
#include <string.h>
#include <storage/common/table_meta.h>
#include <olap_storage/data_chunk.h>

class CLogManager;

class OlapTable {
public:
  OlapTable() = default;
  OlapTable(std::string base_dir)
  {
    this->base_dir_ = base_dir;
  }
  ~OlapTable();

  // the oltp storage and table meta dir
  std::string base_dir_;
  // the olap storage dir
  std::string storage_dir_;

  // table meta message
  TableMeta table_meta_;
  // log
  CLogManager *clog_manager_;
  // table name
  std::string name_;

  DataChunkBuilder *builder_ = nullptr;

  bool is_recovering_ = false;

  void open(const char *meta_file, const char *base_dir, CLogManager *clog_manager);
  void begin_recover();
  void insert(std::vector<Value> values);
  void end_recover();
  void recover();
};
