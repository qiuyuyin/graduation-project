#include <gtest/gtest.h>
#include <fstream>
#include <filesystem>

#include "olap_storage/data_chunk.h"

TEST(StorageMemRowsetTest, AppendAndFlush)
{
  FieldMeta fm1;
  fm1.init("test_field", INTS, 0, 4, true);
  FieldMeta fm2;
  fm2.init("test_field", CHARS, 4, 4, true);
  std::vector<FieldMeta> fileds(0);
  fileds.push_back(fm1);
  fileds.push_back(fm2);
  // Create an instance of StorageMemRowset with 2 columns
  StorageMemRowset rowset(2, fileds);
  // Create a DataChunkBuilder
  DataChunkBuilder builder(2);
  // Add some rows to the DataChunkBuilder
  builder.push_row({Value{INTS, new int(1)}, Value{CHARS, strdup("foo")}});
  builder.push_row({Value{INTS, new int(2)}, Value{CHARS, strdup("bar")}});
  // Add the rows to the StorageMemRowset
  auto chunk = builder.take();
  rowset.append(*chunk);
  // Flush the data and write it to a file
  rowset.flush("/home/yinqiuyu/hust-bishe/miniob/olap");
}