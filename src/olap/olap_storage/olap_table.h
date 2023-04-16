// 在列存初始化的时候会读取行存中已经存在的table元数据，包含有每个列的属性
#include <string.h>
#include <storage/common/table_meta.h>


class OlapTable {
public:
  OlapTable(/* args */);
  ~OlapTable();

  std::string base_dir_;
  TableMeta table_meta_;
};

OlapTable::OlapTable(/* args */)
{}

OlapTable::~OlapTable()
{}
