#include <olap_sql/select.h>
#include <regex>

void ColumnList::extractColumns(string sql)
{
  size_t last_semicolon_pos = sql.find_last_of("\n");
  if (last_semicolon_pos != string::npos) {
      sql.erase(last_semicolon_pos, 1);
  }
  last_semicolon_pos = sql.find_last_of(";");
  if (last_semicolon_pos != string::npos) {
      sql.erase(last_semicolon_pos, 1);
  }
  string select = "select";
  transform(sql.begin(), sql.end(), sql.begin(), ::tolower);
  size_t pos = sql.find(select);
  if (pos == string::npos) {
    return;
  }
  vector<string> fields;
  string field_str = sql.substr(pos + select.length());
  size_t from_pos = field_str.find("from");
  if (from_pos == string::npos) {
    return ;
  }
  string field_list = field_str.substr(0, from_pos);
  string delimiter = ",";
  size_t start = 0;
  size_t end = field_list.find(delimiter);
  while (end != string::npos) {
    fields.push_back(field_list.substr(start, end - start));
    start = end + delimiter.length();
    end = field_list.find(delimiter, start);
  }
  fields.push_back(field_list.substr(start, end - start));

  string table_str = field_str.substr(from_pos + 4);
  size_t start_pos = table_str.find_first_not_of(" \t\n\r");
  size_t end_pos = table_str.find_last_not_of(" \t\n\r");
  string table_name = table_str.substr(start_pos, end_pos - start_pos + 1);
  this->setTableName(table_name);

  for (string field : fields) {
    std::regex pattern("^\\s+|\\s+$");
    auto str = regex_replace(field, pattern, "");
    this->addColumn(str);
  }
  return ;
}