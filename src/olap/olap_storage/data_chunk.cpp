#include <fstream>

#include "olap_storage/data_chunk.h"
#include "zstd.h"
#include "common/io/io.h"
#include "common/os/path.h"


void ColumnBuilder::flush(FieldMeta fm)
{
  int len = fm.len();

  auto vec = this->arrayImpl.array;
  int allLen = len * vec.size();
  char *arrayData = new char[allLen];
  for (int i = 0; i < vec.size(); i++) {
    std::memcpy(arrayData + i * len, vec[i].data, len);
  }
  this->data = arrayData;
  auto afterLen = this->compress(allLen);
  std::cout << "before compress: " << allLen << std::endl;
  std::cout << "after compress: " << afterLen << std::endl;
  this->length = afterLen;
}

size_t ColumnBuilder::compress(int allLen)
{
  size_t inSize = allLen;
  size_t outSize = ZSTD_compressBound(inSize);

  char *outBuff = new char[outSize];
  size_t const compressResult = ZSTD_compress(outBuff, outSize, this->data, inSize, 22);
  if (ZSTD_isError(compressResult)) {
    std::cerr << "Error: " << ZSTD_getErrorName(compressResult) << std::endl;
    return 1;
  }
  this->compressData = outBuff;
  return compressResult;
}

void RowsetBuilder::append(DataChunk chunk)
{
  for(int i=0;i < chunk.arrays.size();i++) {
    ColumnBuilder column_builder;
    column_builder.arrayImpl = chunk.arrays[i];
    this->builders_.push_back(column_builder);
  }
}

EncodedRowset RowsetBuilder::flush()
{
  std::vector<EncodedColumn> encodedColumns;
  encodedColumns.reserve(builders_.size());
  for (int i = 0; i < builders_.size(); i++) {
    builders_[i].flush(fields_[i]);
    EncodedColumn ec;
    ec.length = builders_[i].length;
    ec.data = builders_[i].compressData;
    encodedColumns.push_back(ec);
  }

  EncodedRowset er;
  er.size = encodedColumns.size();
  er.columns = std::move(encodedColumns);

  return er;
}

void StorageMemRowset::write_to_file(std::string path) {
  auto vec = this->rowset_builder_.builders_;
  
  for (int i = 0; i < vec.size(); i++) {
    auto index = std::to_string(i+1);
    auto filename = path + "/" + index + ".col";
    std::ofstream file(filename, std::ios::out | std::ios::trunc);
    common::writeToFile(filename, vec[i].compressData, vec[i].length, "w");
  }
}

void StorageMemRowset::append(DataChunk columns) {
  this->mem_table_.append(columns);
}

void StorageMemRowset::flush(std::string path) {
  auto chunk = this->mem_table_.flush();
  this->rowset_builder_.append(chunk);
  this->rowset_builder_.flush();
  common::check_directory(path);
  
  this->write_to_file(path);
}


