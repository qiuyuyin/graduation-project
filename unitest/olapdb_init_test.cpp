#include <gtest/gtest.h>
#include <vector>
#include <ctime>
#include <sstream>
#include <fstream>
#include <filesystem>

#include "common/defs.h"
#include "common/os/path.h"
#include "storage/common/table.h"
#include "storage/common/table_meta.h"
#include "common/log/log.h"
#include "common/lang/string.h"
#include "storage/clog/clog.h"
#include "olap_db/olap_db.h"

TEST(OlapDBTest, Init)
{
 OlapDB db;   
 db.init("./miniob/olap","./miniob/db/sys");
 db.recover();
 db.recover();

 common::delete_directory("./miniob/olap");
}