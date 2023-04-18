// 在列存初始化的时候会读取行存中已经存在的table元数据，包含有每个列的属性
#include <string.h>
#include <storage/common/table_meta.h>

class CLogManager;

class OlapTable {
public:
  OlapTable() = default;
  OlapTable(std::string base_dir)
  {
    this->base_dir_ = base_dir;
  }
  ~OlapTable();

  std::string base_dir_;
  std::string storage_dir_;
  TableMeta table_meta_;
  CLogManager *clog_manager_;
  std::string name_;

  void open(const char *meta_file, const char *base_dir, CLogManager *clog_manager);
  void insert(std::vector<Value> values);
  void recover();
};
