#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class ColumnList {
public:
    void addColumn(string column) {
        columns.push_back(column);
    }
    vector<string> getColumns() const {
        return columns;
    }
    string getTableName() const {
        return table_name;
    }
    void setTableName(string table) {
        table_name = table;
    }
    void extractColumns(string sql);
private:
    vector<string> columns;
    string table_name;
};

