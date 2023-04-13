#include <gtest/gtest.h>
#include <fstream>
#include "common/io/io.h"


TEST(FileIOTest, ReadWriteFile) {
  // create test file
  const std::string fileName = "testfile.txt";
  std::ofstream outfile(fileName);
  ASSERT_TRUE(outfile.is_open());
  outfile << "Hello, world!";
  outfile.close();

  // read file
  char* data = nullptr;
  size_t fileSize = 0;
  ASSERT_EQ(0, common::readFromFile(fileName, data, fileSize));
  ASSERT_EQ(fileSize, strlen(data));
  ASSERT_STREQ("Hello, world!", data);

  // write file
  const char* newData = "Goodbye, world!";
  ASSERT_EQ(0, common::writeToFile(fileName, newData, strlen(newData), "w"));
  ASSERT_EQ(0, common::readFromFile(fileName, data, fileSize));
  ASSERT_EQ(fileSize, strlen(newData));
  ASSERT_STREQ("Goodbye, world!", data);

  // cleanup
  EXPECT_EQ(0, remove(fileName.c_str()));
  if (data != nullptr) {
    free(data);
  }
}