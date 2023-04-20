#include "gtest/gtest.h"

#include <iostream>
#include <olap_sql/select.h>
using namespace std;

TEST(TestSelectParser, SelectParser)
{
  string sql = "select id, name, age from users";
  ColumnList* columns = ColumnList::extractColumns(sql);
  if(columns == nullptr) {
    cout << "ERR Parse";
  }
  cout << "Table name: " << columns->getTableName() << endl;
  cout << "Selected fields: ";
  for (string column : columns->getColumns()) {
    cout << column << ", ";
  }
  cout << endl;
}
