/* Copyright (c) 2021 Xie Meiyi(xiemeiyi@hust.edu.cn) and OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by wangyunlai on 2022/9/28
//

#include <string>
#include <vector>
#include "util/util.h"

using namespace std;

string double2string(double v)
{
  char buf[256];
  snprintf(buf, sizeof(buf), "%.2f", v);
  size_t len = strlen(buf);
  while (buf[len - 1] == '0') {
    len--;
      
  }
  if (buf[len - 1] == '.') {
    len--;
  }

  return string(buf, len);
}

vector<string> split(const string& str, const string& delim) {
  vector<string> res;
  if("" == str) return res;
  //先将要切割的字符串从string类型转换为char*类型
  char * strs = new char[str.length() + 1] ; //不要忘了
  strcpy(strs, str.c_str());

  char * d = new char[delim.length() + 1];
  strcpy(d, delim.c_str());

  char *p = strtok(strs, d);
  while(p) {
    string s = p; //分割得到的字符串转换为string类型
    res.push_back(s); //存入结果数组
    p = strtok(NULL, d);
  }

  return res;
}

bool has_bit_set(int num, int loc) {
  int temp = 1 << (loc-1);
  return (num & temp) != 0;
}

int set_bit(int num, int loc, bool set) {
  if (set) {
    return (num | (1 << (loc-1)));
  } else {
    return (num & (~(1 << (loc-1))));
  }
}