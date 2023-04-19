#include <iostream>
#include <memory>
#include <vector>
#include <cstring>
#include <string>
#include <sql/parser/parse_defs.h>
#include <storage/common/table_meta.h>

// typedef struct _Value {
//   AttrType type;  // type of value
//   void *data;     // value
// } Value;

// typedef enum
// {
//   UNDEFINED,
//   CHARS,
//   INTS,
//   FLOATS,
//   DATES,
//   TEXTS,
//   NULLS
// } AttrType;

// 定义ArrayImpl类型
struct ArrayImpl {
  std::vector<Value> array;
};

// 定义ArrayBuilderImpl类型
struct ArrayBuilderImpl {
  std::vector<Value> data;
  // 添加一个DataValue到数组
  void push(Value value)
  {
    data.push_back(value);
  }
  // 构建ArrayImpl类型
  ArrayImpl build()
  {
    return {data};
  }
};

// 定义DataChunk类型
class DataChunk {
public:
  // 构造函数
  explicit DataChunk(std::vector<ArrayImpl> arrays) : arrays(std::move(arrays))
  {}
  // 获取数据块中的数组数量
  size_t len() const
  {
    return arrays.size();
  }
  // 获取数据块中的第i个数组
  const ArrayImpl *get_array(size_t i) const
  {
    if (i >= arrays.size()) {
      return nullptr;
    }
    return &arrays[i];
  }
  std::vector<ArrayImpl> arrays;
};

// 定义DataChunkBuilder类型
class DataChunkBuilder {
public:
  explicit DataChunkBuilder()
  {}
  explicit DataChunkBuilder(size_t size)
  {
    std::vector<ArrayBuilderImpl> vec(size);
    this->array_builders = vec;
  }
  // 添加一行数据到数据块
  std::unique_ptr<DataChunk> push_row(const std::vector<Value> &row)
  {
    size_t n = array_builders.size();
    if (n != row.size()) {
      return nullptr;
    }
    for (size_t i = 0; i < n; i++) {
      array_builders[i].push(row[i]);
    }
    return take();
  }
  // 完成数据块的构建
  std::unique_ptr<DataChunk> take()
  {
    std::vector<ArrayImpl> arrays;
    for (auto &builder : array_builders) {
      arrays.push_back(builder.build());
    }
    return std::make_unique<DataChunk>(std::move(arrays));
  }
  std::vector<ArrayBuilderImpl> array_builders;
};

struct ColumnMemTable {
  std::vector<ArrayBuilderImpl> builders;

  explicit ColumnMemTable()
  {}

  explicit ColumnMemTable(size_t column_count) : builders(column_count)
  {}

  void append(const DataChunk &columns)
  {
    const size_t column_count = columns.len();
    for (size_t idx = 0; idx < column_count; idx++) {
      const ArrayImpl *impl = columns.get_array(idx);
      if (impl == nullptr) {
        continue;
      }
      const std::vector<Value> &values = impl->array;
      for (const Value &value : values) {
        builders[idx].push(value);
      }
    }
  }

  DataChunk flush()
  {
    std::vector<ArrayImpl> arrays;
    arrays.reserve(builders.size());
    for (auto &builder : builders) {
      arrays.emplace_back(builder.build());
    }
    return DataChunk(std::move(arrays));
  }
};

class ColumnBuilder {
public:
  int length;
  char *data;
  char *compressData;
  ArrayImpl arrayImpl;

  void flush(FieldMeta fm);
  size_t compress(int allLen);
};

class EncodedColumn {
public:
  int length;
  char *data;
};

class EncodedRowset {
public:
  size_t size;
  std::vector<EncodedColumn> columns;
};

// File Encode

class RowsetBuilder {
public:
  std::vector<FieldMeta> fields_;
  std::vector<ColumnBuilder> builders_;

  EncodedRowset flush();
  void append(DataChunk chunk);
};

class StorageMemRowset {
public:
  ColumnMemTable mem_table_;
  RowsetBuilder rowset_builder_;

  void append(DataChunk columns);
  void write_to_file(std::string path);
  void flush(std::string path);
  // size是当前列的数目
  StorageMemRowset(size_t size,const std::vector<FieldMeta> fileds) : mem_table_(size), rowset_builder_()
  {
    this->rowset_builder_.fields_ = fileds;
  }
};
