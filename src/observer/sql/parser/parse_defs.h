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
// Created by Meiyi
//

#ifndef __OBSERVER_SQL_PARSER_PARSE_DEFS_H__
#define __OBSERVER_SQL_PARSER_PARSE_DEFS_H__

#include <stddef.h>
#include <stdint.h>


#define MAX_NUM 20
#define MAX_REL_NAME 20
#define MAX_ATTR_NAME 20
#define MAX_ERROR_MESSAGE 20
#define MAX_DATA 50



typedef enum  {
  MAX,
  MIN,
  COUNT,
  AVG,
  SUM,
  NO_Aggregation
} AggregationType;


// 属性结构体
typedef struct {
  char *relation_name;   // relation name (may be NULL) 表名
  char *attribute_name;  // attribute name              属性名
  AggregationType aggregation_type; //聚合函数类型
} RelAttr;



typedef enum {
  EQUAL_TO,     //"="     0
  LESS_EQUAL,   //"<="    1
  NOT_EQUAL,    //"<>"    2
  LESS_THAN,    //"<"     3
  GREAT_EQUAL,  //">="    4
  GREAT_THAN,   //">"     5
  LIKE,         //"like"  6
  NOT_LIKE,     //"not like" 7"
  NO_OP
} CompOp;

// 属性值类型
typedef enum {
  UNDEFINED,
  CHARS,
  INTS,
  FLOATS,
  DATES,
  TEXT,
  NUM_OF_ATTRTYPE,
} AttrType;

// 属性值
// layout of date is quite important!
// 小端法
typedef struct _Date {
  int8_t day;
  int8_t month;
  int16_t year;
} Date;

typedef struct _Value {
  AttrType type;  // type of value
  void *data;     // value
} Value;


typedef struct {
  int has_alias;
  char alias[20]; //表达式的别名
  size_t expr_cell_num; //表达式有几个cell
  char data[50][20]; //表达式cell数据
} Expr;

typedef struct _Condition {
  int left_type;    // 1代表是Value 2代表RelAttr 3代表计算表达式(单一聚合函数也属于这一类)

  Value left_value;    // left-hand side value if left_type = FALSE
  RelAttr left_attr;   // left-hand side attribute
  Expr left_expr;      // 左边是计算表达式

  CompOp comp;         // comparison operator
  int right_type;   // TRUE if right-hand side is an attribute
                       // 1时，操作符右边是属性名，0时，是属性值

  RelAttr right_attr;  // right-hand side attribute if right_type = TRUE 右边的属性
  Value right_value;   // right-hand side value if right_type = FALSE
  Expr right_expr;     // 右边是计算表达式
} Condition;

typedef struct {
  size_t attr_num;
  RelAttr attributes[MAX_NUM];
  size_t having_condition_num;
  Condition having_condition[MAX_NUM];
} GroupBy;

typedef struct {
  int value_pos;
  int type;
  char* data[20];
} ExprCellBuffer;



typedef struct {
  size_t exprs_num;
  Expr exprs[20];
} ExprList;



typedef struct {
  char* alias;
  char* name;
} Relation;

// struct of select
typedef struct {
  size_t attr_num;                // Length of attrs in Select clause
  RelAttr attributes[MAX_NUM];    // attrs in Select clause
  size_t relation_num;            // Length of relations in Fro clause
  Relation relations[MAX_NUM]; // relations in From clause
  size_t condition_num;           // Length of conditions in Where clause
  Condition conditions[MAX_NUM];  // conditions in Where clause
  GroupBy group_by;
  //expression
  ExprList expr_list;
} Selects;



// struct of insert
typedef struct {
  char *relation_name;    // Relation to insert into
  size_t value_num;       // Length of values
  size_t tuple_num;
  int tuple_size[MAX_NUM];
  Value values[MAX_NUM];  // values to insert
} Inserts;

// struct of delete
typedef struct {
  char *relation_name;            // Relation to delete from
  size_t condition_num;           // Length of conditions in Where clause
  Condition conditions[MAX_NUM];  // conditions in Where clause
} Deletes;

// struct of update
typedef struct {
  char *relation_name;            // Relation to update
  char *attribute_name;           // Attribute to update
  Value value;                    // update value
  size_t condition_num;           // Length of conditions in Where clause
  Condition conditions[MAX_NUM];  // conditions in Where clause
} Updates;

typedef struct {
  char *name;     // Attribute name
  AttrType type;  // Type of attribute
  size_t length;  // Length of attribute
} AttrInfo;

// struct of craete_table
typedef struct {
  char *relation_name;           // Relation name
  size_t attribute_count;        // Length of attribute
  AttrInfo attributes[MAX_NUM];  // attributes
} CreateTable;

// struct of drop_table
typedef struct {
  char *relation_name;  // Relation name
} DropTable;

// struct of create_index
typedef struct {
  char *index_name;      // Index name
  char *relation_name;   // Relation name
  char *attribute_name;  // Attribute name
} CreateIndex;

// struct of  drop_index
typedef struct {
  const char *index_name;  // Index name
} DropIndex;

typedef struct {
  const char*relation_name;
} ShowIndex;

typedef struct {
  const char *relation_name;
} DescTable;

typedef struct {
  const char *relation_name;
  const char *file_name;
} LoadData;

union Queries {
  Selects selection;
  Inserts insertion;
  Deletes deletion;
  Updates update;
  CreateTable create_table;
  DropTable drop_table;
  CreateIndex create_index;
  DropIndex drop_index;
  ShowIndex show_index;
  DescTable desc_table;
  LoadData load_data;
  char *errors;
};

// 修改yacc中相关数字编码为宏定义
enum SqlCommandFlag {
  SCF_ERROR = 0,
  SCF_SELECT,
  SCF_INSERT,
  SCF_UPDATE,
  SCF_DELETE,
  SCF_CREATE_TABLE,
  SCF_DROP_TABLE,
  SCF_CREATE_INDEX,
  SCF_DROP_INDEX,
  SCF_SHOW_INDEX,
  SCF_SYNC,
  SCF_SHOW_TABLES,
  SCF_DESC_TABLE,
  SCF_BEGIN,
  SCF_COMMIT,
  SCF_CLOG_SYNC,
  SCF_ROLLBACK,
  SCF_LOAD_DATA,
  SCF_HELP,
  SCF_EXIT
};
// struct of flag and sql_struct
typedef struct Query {
  const char* sql;
  enum SqlCommandFlag flag;
  union Queries sstr;
} Query;

#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus

const char *aggregate_type_to_string(AggregationType type);

void append_buffer_expr_to_select_exprlist(ExprList* target, ExprCellBuffer* cells, size_t num);
void append_buffer_expr_to_select_attribute(Selects *selects, ExprCellBuffer* cells, size_t num);
void build_condition_by_buffer_expr(CompOp comp, Value* buffer_values, Condition* condition, ExprCellBuffer* cells, size_t pos1, size_t pos2);



void append_alias_to_expr(ExprList* expr_list, char* alias);

void set_buffer_expr_cell(ExprCellBuffer* expr_cell, int type, char* param1, char* param2, char* param3);

void set_buffer_expr_cell_value_pos(ExprCellBuffer *expr_cell, int pos);




void relation_attr_init(RelAttr *relation_attr, const char *relation_name, const char *attribute_name, const char *aggregation_type);
void relation_attr_destroy(RelAttr *relation_attr);

char* value_to_string(Value* value);
int value_init_date(Value *value, const char *v);
int value_init_date_from_integer(Value *value, int v);
void value_init_integer(Value *value, int v);
void value_init_float(Value *value, float v);
void value_init_string(Value *value, const char *v);
void value_destroy(Value *value);

void condition_init(Condition *condition, CompOp comp, int left_type, Value *left_value, RelAttr *left_attr, Expr *left_expr,
    int right_type, Value *right_value, RelAttr *right_attr, Expr *right_expr);
void condition_destroy(Condition *condition);
void groupby_destroy(GroupBy *groupBy);
void expr_list_destroy(ExprList* exprList);

void attr_info_init(AttrInfo *attr_info, const char *name, AttrType type, size_t length);
void attr_info_destroy(AttrInfo *attr_info);

void selects_init(Selects *selects, ...);
void selects_append_attribute(Selects *selects, RelAttr *rel_attr);
void groupby_append_attribute(Selects *selects, RelAttr *rel_attr);
void selects_append_relation(Selects *selects, const char *relation_name, const char *alias_name);
void selects_append_conditions(Selects *selects, Condition conditions[], size_t condition_num);
void relation_destroy(Relation* relation);
void selects_destroy(Selects *selects);
void clear_buffer_expr_cell_list(ExprCellBuffer* exprCellBuffer, int len);

void inserts_init(Inserts *inserts, const char *relation_name, Value values[], size_t value_num);
void inserts_destroy(Inserts *inserts);

void deletes_init_relation(Deletes *deletes, const char *relation_name);
void deletes_set_conditions(Deletes *deletes, Condition conditions[], size_t condition_num);
void deletes_destroy(Deletes *deletes);

void updates_init(Updates *updates, const char *relation_name, const char *attribute_name, Value *value,
    Condition conditions[], size_t condition_num);
void updates_destroy(Updates *updates);

void create_table_append_attribute(CreateTable *create_table, AttrInfo *attr_info);
void create_table_init_name(CreateTable *create_table, const char *relation_name);
void create_table_destroy(CreateTable *create_table);

void drop_table_init(DropTable *drop_table, const char *relation_name);
void drop_table_destroy(DropTable *drop_table);

void create_index_init(
    CreateIndex *create_index, const char *index_name, const char *relation_name, const char *attr_name);
void create_index_destroy(CreateIndex *create_index);

void drop_index_init(DropIndex *drop_index, const char *index_name);
void drop_index_destroy(DropIndex *drop_index);

void show_index_init(ShowIndex *show_index, const char* relation_name);
void show_index_destroy(ShowIndex *show_index);

void desc_table_init(DescTable *desc_table, const char *relation_name);
void desc_table_destroy(DescTable *desc_table);

void load_data_init(LoadData *load_data, const char *relation_name, const char *file_name);
void load_data_destroy(LoadData *load_data);

void query_init(Query *query);
Query *query_create();  // create and init
void query_reset(Query *query);
void query_destroy(Query *query);  // reset and delete

#ifdef __cplusplus
}
#endif  // __cplusplus

#endif  // __OBSERVER_SQL_PARSER_PARSE_DEFS_H__
