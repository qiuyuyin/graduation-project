#include <vector>
#include <string>
#include <unordered_map>

#include "sql/parser/parse_defs.h"
#include "storage/clog/clog.h"
#include "olap_table/olap_table.h"
#include "common/log/log.h"
#include "common/os/path.h"
#include "storage/common/meta_util.h"
#include "common/defs.h"
#include "storage/common/table.h"
#include "storage/common/table_meta.h"
#include "common/lang/string.h"

class OlapDB {
public:
  std::string olap_path_;
  std::string oltp_path_;
  std::unordered_map<std::string, OlapTable *> opened_tables_;
  CLogManager *clog_manager_ = nullptr;
  int trx_ = 0;

  OlapDB() = default;
  ~OlapDB() = default ;
  void init(std::string olap_path,std::string oltp_path);
  void open_all_tables();
  void recover();
  void select(std::string sql);
  OlapTable* find_table(const char *table_name) const;
};
