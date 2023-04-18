#include <vector>
#include <string>
#include <unordered_map>

#include "sql/parser/parse_defs.h"
#include "storage/clog/clog.h"

class Table;
class OlapTable;

class OlapDB {
public:
  std::string olap_path_;
  std::string oltp_path_;
  std::unordered_map<std::string, OlapTable *> opened_tables_;
  CLogManager *clog_manager_ = nullptr;

  OlapDB();
  ~OlapDB();
  void init(std::string olap_path,std::string oltp_path);
  void open_all_tables();
  void recover();
  OlapTable* find_table(const char *table_name) const;

};

OlapDB::OlapDB()
{}

OlapDB::~OlapDB()
{}
