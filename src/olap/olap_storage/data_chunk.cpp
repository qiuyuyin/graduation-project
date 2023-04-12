#include "./data_chunk.h"
#include "zstd.h"

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
  return compressResult;
}

EncodedRowset RowsetBuilder::flush()
{
  std::vector<EncodedColumn> encodedColumns;
  encodedColumns.reserve(builders_.size());
  for (int i = 0; i < builders_.size(); i++) {
    builders_[i].flush(fields_[i]);
    EncodedColumn ec;
    ec.index = builders_[i].index;
    ec.data = builders_[i].compressData;
    encodedColumns.push_back(ec);
  }

  EncodedRowset er;
  er.size = encodedColumns.size();
  er.columns = std::move(encodedColumns);

  return er;
}
