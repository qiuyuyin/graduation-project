#include <gtest/gtest.h>
#include <olap_storage/data_chunk.h>
#include <limits.h>
#include <string.h>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <fstream>
#include <filesystem>
#include <cstdio>


#include "common/defs.h"
#include "storage/common/table.h"
#include "storage/common/table_meta.h"
#include "common/log/log.h"
#include "common/lang/string.h"
#include "storage/default/disk_buffer_pool.h"
#include "storage/record/record_manager.h"
#include "storage/common/condition_filter.h"
#include "storage/common/meta_util.h"
#include "storage/index/index.h"
#include "storage/common/field.h"

TEST(FstreamTest, OpenFile)
{
  TableMeta table_meta_;
  std::fstream fs;
  std::string meta_file_path = std::string("/home/yinqiuyu/hust-bishe/miniob-2022/build/miniob/db/sys") +
                               common::FILE_PATH_SPLIT_STR + "mem2.table";
  fs.open(meta_file_path, std::ios_base::in | std::ios_base::binary);
  if (!fs.is_open()) {
    LOG_ERROR("Failed to open meta file for read. file name=%s, errmsg=%s", meta_file_path.c_str(), strerror(errno));
  }
  if (table_meta_.deserialize(fs) < 0) {
    LOG_ERROR("Failed to deserialize table meta. file name=%s", meta_file_path.c_str());
    fs.close();
  }
  fs.close();
}

TEST(ColumnBuilderTest, CompressIntTest)
{
  // Create some input data
  FieldMeta fm;
  fm.init("test_field", INTS, 0, 4, true);
  std::srand(std::time(nullptr));
  // 生成随机数
  const int min = 1, max = 1000;
  ArrayBuilderImpl builder;
  for (size_t i = 0; i < 1000; i++) {
    int randomNumber = min + std::rand() % (max - min + 1);
    builder.push({INTS, new int(randomNumber)});
  }
  ArrayImpl array = builder.build();
  ColumnBuilder cb;
  cb.arrayImpl = array;
  cb.flush(fm);
}


TEST(ColumnBuilderTest, CompressStringTest)
{
  // Create some input data
  FieldMeta fm;
  fm.init("test_field", CHARS, 0, 10, true);
  std::srand(std::time(nullptr));
  // 生成随机数
  ArrayBuilderImpl builder;
  for (size_t i = 0; i < 1000; i++) {
    char* myString = "Helloworld";
    builder.push({CHARS, myString});
  }
  ArrayImpl array = builder.build();
  ColumnBuilder cb;
  cb.arrayImpl = array;
  cb.flush(fm);
}

TEST(ColumnMemTableTest, AppendAndFlush)
{
  // Define a data chunk with two columns: one with integers and one with strings
  std::vector<ArrayImpl> arrays;
  ArrayBuilderImpl int_builder;
  int_builder.push({AttrType::INTS, new int(1)});
  int_builder.push({AttrType::INTS, new int(2)});
  int_builder.push({AttrType::INTS, new int(3)});
  arrays.push_back(int_builder.build());
  ArrayBuilderImpl str_builder;
  str_builder.push({AttrType::CHARS, new std::string("foo")});
  str_builder.push({AttrType::CHARS, new std::string("bar")});
  str_builder.push({AttrType::CHARS, new std::string("baz")});
  arrays.push_back(str_builder.build());
  DataChunk data_chunk(arrays);

  // Create a column memtable with two builders for the two columns
  ColumnMemTable memtable(2);

  // Append the data chunk to the memtable
  memtable.append(data_chunk);

  // Flush the memtable and get the resulting data chunk
  DataChunk flushed_chunk = memtable.flush();
  ASSERT_EQ(flushed_chunk.len(), 2);
  const ArrayImpl *int_array = flushed_chunk.get_array(0);
  ASSERT_EQ(int_array->array.size(), 3);
  ASSERT_EQ(static_cast<int *>(int_array->array[0].data)[0], 1);
  ASSERT_EQ(static_cast<int *>(int_array->array[1].data)[0], 2);
  ASSERT_EQ(static_cast<int *>(int_array->array[2].data)[0], 3);
  const ArrayImpl *str_array = flushed_chunk.get_array(1);
  ASSERT_EQ(str_array->array.size(), 3);
  ASSERT_EQ(*static_cast<std::string *>(str_array->array[0].data), "foo");
  ASSERT_EQ(*static_cast<std::string *>(str_array->array[1].data), "bar");
  ASSERT_EQ(*static_cast<std::string *>(str_array->array[2].data), "baz");
}

TEST(DataChunkBuilderTest, PushRow)
{
  DataChunkBuilder builder;

  // 添加一些列
  builder.array_builders.push_back(ArrayBuilderImpl());
  builder.array_builders.back().push({FLOATS, new float(1.0)});
  builder.array_builders.push_back(ArrayBuilderImpl());
  builder.array_builders.back().push({TEXT, new std::string("hello")});

  // 添加一行数据
  std::vector<Value> row = {{FLOATS, new float(2.0)}, {TEXT, new std::string("world")}};
  auto chunk = builder.push_row(row);

  // 验证数据块中的数组数量是否正确
  ASSERT_EQ(chunk->len(), 2);

  // 验证数据块中的第一个数组是否正确
  auto array1 = chunk->get_array(0);
  ASSERT_NE(array1, nullptr);
  ASSERT_EQ(array1->array.size(), 2);
  ASSERT_EQ(array1->array[0].type, FLOATS);
  ASSERT_FLOAT_EQ(*(float *)array1->array[0].data, 1.0);
  ASSERT_EQ(array1->array[1].type, FLOATS);
  ASSERT_FLOAT_EQ(*(float *)array1->array[1].data, 2.0);

  // 验证数据块中的第二个数组是否正确
  auto array2 = chunk->get_array(1);
  ASSERT_NE(array2, nullptr);
  ASSERT_EQ(array2->array.size(), 2);
  ASSERT_EQ(array2->array[0].type, TEXT);
  ASSERT_EQ(*(std::string *)array2->array[0].data, "hello");
  ASSERT_EQ(array2->array[1].type, TEXT);
  ASSERT_EQ(*(std::string *)array2->array[1].data, "world");
}

TEST(DataChunkBuilderTest, PushRowWithIncorrectSize)
{
  DataChunkBuilder builder(2);
  

  // 添加一行数据，但是列数不正确
  std::vector<Value> row = {
      {FLOATS, new float(1.0)},
      {INTS, new int(2)},
  };
  auto chunk = builder.push_row(row);

  // 验证返回值是否为nullptr
  ASSERT_NE(chunk, nullptr);
}

TEST(DataChunkTest, GetArrayWithIncorrectIndex)
{
  DataChunkBuilder builder;
  builder.array_builders.push_back(ArrayBuilderImpl());
  auto chunk = builder.take();

  // 获取一个不存在的数组
  auto array = chunk->get_array(1);

  // 验证返回值是否为nullptr
  ASSERT_EQ(array, nullptr);
}

// TEST(StorageMemRowsetTest, WriteToFileTest2) {
//   // Create a temporary directory for testing
//   // std::string temp_dir = std::filesystem::temp_directory_path().string();
//   std::string temp_dir = "";
//   std::string test_dir = temp_dir + "/tmp";
//   std::filesystem::create_directory(test_dir);

//   // Create a sample DataChunk
//   std::vector<ArrayImpl> arrays;
//   ArrayBuilderImpl int_builder;
//   for(int i=0;i < 200;i++) {
//     int_builder.push({AttrType::INTS, new int(i)});
//   }
  
//   arrays.push_back(int_builder.build());
//   DataChunk data_chunk(arrays);

//   // Create a ColumnMemTable and append the sample DataChunk
//   ColumnMemTable mem_table(1);
//   mem_table.append(data_chunk);

//   // Create a RowsetBuilder and a ColumnBuilder
//   RowsetBuilder rowset_builder;
//   ColumnBuilder column_builder;
//   column_builder.arrayImpl = mem_table.flush().arrays[0];
//   rowset_builder.builders_.push_back(column_builder);
  // FieldMeta fm1;
  // fm1.init("test_field", INTS, 0, 4, true);
  // rowset_builder.flush();
  // std::vector<FieldMeta> fileds(0);
  // fileds.push_back(fm1);
//   // Create a StorageMemRowset and write to file
//   StorageMemRowset mem_rowset(1,fileds);
//   mem_rowset.rowset_builder_ = rowset_builder;
//   mem_rowset.write_to_file(test_dir);

//   // Check if the file was written correctly
//   std::string filename = test_dir + "/1.col";
//   std::ifstream file(filename, std::ios::in | std::ios::binary);
//   ASSERT_TRUE(file.good());
//   char buffer[1024];
//   file.read(buffer, sizeof(buffer));
//   EXPECT_EQ(file.gcount(), rowset_builder.builders_[0].length);
//   EXPECT_EQ(std::memcmp(buffer, rowset_builder.builders_[0].compressData, rowset_builder.builders_[0].length), 0);

//   // Clean up the temporary directory
//   // std::filesystem::remove_all(test_dir);
// }