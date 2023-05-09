// 在列存初始化的时候会读取行存中已经存在的table元数据，包含有每个列的属性
#include <string.h>
#include <storage/common/table_meta.h>
#include <olap_storage/data_chunk.h>
#include <olap_sql/select.h>
#include "common/defs.h"
#include "storage/common/table.h"
#include "storage/common/table_meta.h"
#include "common/log/log.h"
#include "common/lang/string.h"
#include "storage/clog/clog.h"
#include "common/os/path.h"
#include "common/io/io.h"
#include <util/util.h>


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

  int row_set_id_ = 0;

  DataChunkBuilder *builder_ = nullptr;

  bool is_recovering_ = false;

  vector<int> delete_list;

  void open(const char *meta_file, const char *base_dir, std::string storage_dir, CLogManager *clog_manager);
  void begin_recover();
  void insert(std::vector<Value> values);
  void end_recover();
  void recover();
  void compact();
  std::string select(std::vector<std::string> cols);
  void read_col(int col_index, std::vector<Value>& colValue);
  void select_sql(std::string sql);
  std::string to_string(Value &value, const FieldMeta *filed);
};
