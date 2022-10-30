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

#include <mutex>
#include "sql/parser/parse.h"
#include "rc.h"
#include "common/log/log.h"

RC parse(char *st, Query *sqln);

#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus

const char* AGGREGATE_TYPE_NAME[] = {"max", "min", "count", "avg", "sum"};
const char *aggregate_type_to_string(AggregationType type)
{
  if (type >= MAX && type < NO_Aggregation) {
    return AGGREGATE_TYPE_NAME[type];
  }
  return "unknown";
}

const AggregationType string_to_aggregate_type(const char* s) {
  char* temp = strdup(s);
  for (int i = 0; i < strlen(temp); ++i) {
    temp[i] = tolower(temp[i]);
  }
  for (int i = 0; i < 5; ++i) {
    if (strcmp(temp, AGGREGATE_TYPE_NAME[i]) == 0) {
      return AggregationType(i);
    }
  }
  return NO_Aggregation;
}



void set_buffer_expr_cell(ExprCellBuffer *expr_cell, int type, char* param1, char* param2, char* param3) {
  expr_cell->type = type;
  expr_cell->value_pos = -1;
  char* temp[] = {param1, param2, param3};
  for (int i = 0; i < 3; ++i) {
    if (temp[i] != nullptr) {
      expr_cell->data[i] = strdup(temp[i]);
    } else {
      expr_cell->data[i] = nullptr;
    }
  }
}
void set_buffer_expr_cell_value_pos(ExprCellBuffer *expr_cell, int pos) {
  expr_cell->value_pos = pos;
}

void append_buffer_expr_to_select_exprlist(ExprList* target, ExprCellBuffer* cells, size_t num) {
  auto append = [&](char* str) {
    Expr* expr = &target->exprs[target->exprs_num];
    for (int i = 0; i < strlen(str); ++i) {
      expr->data[expr->expr_cell_num][i] = str[i];
    }
    expr->expr_cell_num++;
  };

  char temp[100];
  for (int i = 0; i < num; ++i) {
    auto cell = cells[i];
    switch (cell.type) {
      case 1:
        append(cell.data[0]);
        break;
      case 2:
        sprintf(temp, "%s.%s", cell.data[0], cell.data[1]);
        append(temp);
        break ;
      case 3:
        sprintf(temp, "%s(%s)", cell.data[0], cell.data[1]);
        append(temp);
        break ;
      case 4:
        sprintf(temp, "%s(%s.%s)", cell.data[0], cell.data[1], cell.data[2]);
        append(temp);
        break ;
      case 5:
        append("count(*)");
        break ;
      case 6:
        append("count(1)");
        break ;
      case 7:
      case 8:
      case 9:
      case 10:
      case 11:
      case 12:
        append(cell.data[0]);
        break ;
    }
  }
}
void append_buffer_expr_to_select_attribute(Selects *selects, ExprCellBuffer* cells, size_t num) {
  for (int i = 0; i < num; ++i) {
    auto cell = cells[i];
    RelAttr attr;
    switch (cell.type) {
      case 1:
        relation_attr_init(&attr, nullptr, cell.data[0], nullptr);
        break ;
      case 2:
        relation_attr_init(&attr, cell.data[0], cell.data[1], nullptr);
        break ;
      case 3:
        relation_attr_init(&attr, nullptr, cell.data[1], cell.data[0]);
        break ;
      case 4:
        relation_attr_init(&attr, cell.data[1], cell.data[2], cell.data[0]);
        break ;
      case 5:
        relation_attr_init(&attr, nullptr, "*", cell.data[0]);
        break ;
      case 6:
        relation_attr_init(&attr, nullptr, cell.data[1], cell.data[0]);
        break ;
    }
    if (cell.type >= 1 && cell.type <= 6) {
      selects_append_attribute(selects, &attr);
    }
  }
}
void build_condition_by_buffer_expr(CompOp comp, Value* buffer_values, Condition* condition, ExprCellBuffer* cells, size_t pos1, size_t pos2) {
  Value *left_value = nullptr, *right_value = nullptr;
  RelAttr *left_attr = nullptr, *right_attr = nullptr;
  Expr *left_expr = nullptr, *right_expr = nullptr;

  auto build = [](Value*& buffer_values, Value*& value, RelAttr*& attr, Expr*& expr, ExprCellBuffer* cells, size_t len){
    auto build_attr = [](ExprCellBuffer& cell){
      RelAttr* attr = new RelAttr;
      if (cell.type == 1) {
        relation_attr_init(attr, nullptr, cell.data[0], nullptr);
      } else if (cell.type == 2) {
        relation_attr_init(attr, cell.data[0], cell.data[1], nullptr);
      }
      return attr;
    };
    ExprList* exprList = new ExprList;
    memset(exprList, 0, sizeof(ExprList));
    if (len == 1) {
      if (cells[0].type == 7) {
        value = &buffer_values[cells[0].value_pos];
      } else if (cells[0].type == 1 || cells[0].type == 2) {
        attr = build_attr(cells[0]);
      } else {
        append_buffer_expr_to_select_exprlist(exprList, cells, 1);
        expr = &exprList->exprs[0];
      }
    } else {
      append_buffer_expr_to_select_exprlist(exprList, cells, len);
      expr = &exprList->exprs[0];
    }
  };

  build(buffer_values, left_value, left_attr, left_expr, cells, pos1);
  build(buffer_values, right_value, right_attr, right_expr, &cells[pos1], pos2-pos1);
  auto get_value = [&](bool left){
    auto value = left ? left_value : right_value;
    auto attr = left ? left_attr : right_attr;
    auto expr = left ? left_expr : right_expr;
    if (value != nullptr) return 1;
    if (attr != nullptr) return 2;
    if (expr != nullptr) return 3;
    return 0;
  };
  condition_init(condition, comp, get_value(true), left_value, left_attr, left_expr, get_value(false), right_value, right_attr, right_expr);
}


void append_alias_to_expr(ExprList* expr_list, char* alias)
{
  expr_list->exprs[expr_list->exprs_num].has_alias = 1;
  for (int i = 0; i < strlen(alias); ++i) {
    expr_list->exprs[expr_list->exprs_num].alias[i] = alias[i];
  }
}

void relation_attr_init(RelAttr *relation_attr, const char *relation_name, const char *attribute_name, const char* aggregation_type)
{
  if (relation_name != nullptr) {
    relation_attr->relation_name = strdup(relation_name);
  } else {
    relation_attr->relation_name = nullptr;
  }
  relation_attr->attribute_name = strdup(attribute_name);
  relation_attr->aggregation_type = AggregationType::NO_Aggregation;
  if (aggregation_type != nullptr) {
    if (strcmp("max", aggregation_type) == 0 || strcmp("MAX", aggregation_type) == 0) {
      relation_attr->aggregation_type = AggregationType::MAX;
    } else if (strcmp("min", aggregation_type) == 0 || strcmp("MIN", aggregation_type) == 0) {
      relation_attr->aggregation_type = AggregationType::MIN;
    } else if (strcmp("count", aggregation_type) == 0 || strcmp("COUNT", aggregation_type) == 0) {
      relation_attr->aggregation_type = AggregationType::COUNT;
    } else if (strcmp("avg", aggregation_type) == 0 || strcmp("AVG", aggregation_type) == 0) {
      relation_attr->aggregation_type = AggregationType::AVG;
    } else if (strcmp("sum", aggregation_type) == 0 || strcmp("SUM", aggregation_type) == 0) {
      relation_attr->aggregation_type = AggregationType::SUM;
    }
  }
}

void relation_attr_destroy(RelAttr *relation_attr)
{
  free(relation_attr->relation_name);
  free(relation_attr->attribute_name);
  relation_attr->relation_name = nullptr;
  relation_attr->attribute_name = nullptr;
}

static bool check_date(int y, int m, int d)
{
  static int mon[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  bool leap = (y % 400 == 0 || (y % 100 && y % 4 == 0));

  return y > 0 && (m > 0) && (m <= 12) && (d > 0) && (d <= ((m == 2 && leap) ? 1 : 0) + mon[m]);
}

char* value_to_string(Value* value) {
  char* temp = new char[20];
  switch (value->type) {
    case CHARS:
      return (char *)value->data;
    case INTS:{
      sprintf(temp, "%d", *(int*)value->data);
      return temp;
    }
    case FLOATS:{
      sprintf(temp, "%f",*(float*)value->data);
      return temp;
    }
    case DATES: {
      Date date = *(Date*)value->data;
      sprintf(temp, "%d-%d-%d", (int)date.year, (int)date.month, (int)date.day);
      return temp;
    }
    case UNDEFINED: {
      sprintf(temp, "%s", "null");
      return temp;
    }
  }
}

int value_init_date(Value *value, const char *v)
{
  value->type = DATES;
  int y, m, d;
  sscanf(v, "%d-%d-%d", &y, &m, &d);
  if (!check_date(y, m, d)) {
    LOG_ERROR("Failed to init %s as date", v);
    return -1;
  }
  value->data = malloc(sizeof (Date));
  auto date_ptr = static_cast<Date *>(value->data);
  date_ptr->year = y;
  date_ptr->month = m;
  date_ptr->day = d;
  return 0;
}
// init from
int value_init_date_from_integer(Value *value, int v){
  value->type = DATES;
  Date *dv = reinterpret_cast<Date *>(&v);
  if (!check_date(dv->year, dv->month, dv->day)) {
    return RC::INVALID_ARGUMENT;
  }
  value->data = malloc(sizeof (Date));
  memcpy(value->data, dv, sizeof(Date));
}
void value_init_integer(Value *value, int v)
{
  value->type = INTS;
  value->data = malloc(sizeof(v));
  memcpy(value->data, &v, sizeof(v));
}
void value_init_float(Value *value, float v)
{
  value->type = FLOATS;
  value->data = malloc(sizeof(v));
  memcpy(value->data, &v, sizeof(v));
}
void value_init_string(Value *value, const char *v)
{
  value->type = CHARS;
  value->data = strdup(v);
}
void value_destroy(Value *value)
{
  value->type = UNDEFINED;
  free(value->data);
  value->data = nullptr;
}

void condition_init(Condition *condition, CompOp comp, int left_type, Value *left_value, RelAttr *left_attr, Expr* left_expr, int right_type, Value *right_value, RelAttr *right_attr, Expr* right_expr)
{
  condition->comp = comp;
  condition->left_type = left_type;
  if (left_type == 1) {
    condition->left_value = *left_value;
  } else if (left_type == 2) {
    condition->left_attr = *left_attr;
  } else if (left_type == 3) {
    condition->left_expr = *left_expr;
  }

  condition->right_type = right_type;
  if (right_type == 1) {
    condition->right_value = *right_value;
  } else if (right_type == 2) {
    condition->right_attr = *right_attr;
  } else if (right_type == 3) {
    condition->right_expr = *right_expr;
  }
}


void expr_destroy(Expr* expr) {
  expr->has_alias = 0;
  expr->expr_cell_num = 0;
  memset(&expr->alias, 0, sizeof(expr->alias));
  memset(&expr->data, 0, sizeof(expr->data));
}

void condition_destroy(Condition *condition)
{
  if (condition->left_type == 1) {
    value_destroy(&condition->left_value);
  } else if (condition->left_type == 2){
    relation_attr_destroy(&condition->left_attr);
  } else if (condition->left_type == 3) {
    expr_destroy(&condition->left_expr);
  }

  if (condition->right_type == 1) {
    value_destroy(&condition->right_value);
  } else if (condition->right_type == 2) {
    relation_attr_destroy(&condition->right_attr);
  } else if (condition->right_type == 3) {
    expr_destroy(&condition->right_expr);
  }
}

void groupby_destroy(GroupBy *groupBy) {
  for (int i = 0; i < groupBy->attr_num; ++i) {
    relation_attr_destroy(&groupBy->attributes[i]);
  }
  for (int i = 0; i < groupBy->having_condition_num; ++i) {
    condition_destroy(&groupBy->having_condition[i]);
  }
  groupBy->attr_num = 0;
  groupBy->having_condition_num = 0;
}

void orderby_destroy(OrderBy *orderBy){
  for(int i = 0; i<orderBy->order_info_num;i++){
    relation_attr_destroy(&orderBy->attrs[i]);
  }
  memset(orderBy,0,sizeof(OrderBy));
}

void expr_list_destroy(ExprList* exprList) {
  memset(exprList, 0, sizeof(ExprList));
}


void attr_info_init(AttrInfo *attr_info, const char *name, AttrType type, size_t length, int nullable)
{
  attr_info->name = strdup(name);
  if(type == TEXT){
    attr_info->type = CHARS;
    attr_info->length = 4096;
    return;
  }
  attr_info->type = type;
  attr_info->length = length;
  attr_info->nullable = nullable;
}



void attr_info_destroy(AttrInfo *attr_info)
{
  free(attr_info->name);
  attr_info->name = nullptr;
}

void selects_init(Selects *selects, ...);
void selects_append_attribute(Selects *selects, RelAttr *rel_attr)
{
  selects->attributes[selects->attr_num++] = *rel_attr;
}
void groupby_append_attribute(Selects *selects, RelAttr *rel_attr)
{
  selects->group_by.attributes[selects->group_by.attr_num++] = *rel_attr;
}
void selects_append_relation(Selects *selects, const char *relation_name, const char *alias)
{
  selects->relations[selects->relation_num].name = strdup(relation_name);
  if (alias != nullptr) {
    selects->relations[selects->relation_num++].alias = strdup(alias);
  } else {
    selects->relations[selects->relation_num++].alias = nullptr;
  }
}

void selects_append_order_by_attr(Selects *selects, RelAttr *rel_attr,OrderType od_type){
  selects->order_by.attrs[selects->order_by.order_info_num] = *rel_attr;
  selects->order_by.od_types[selects->order_by.order_info_num] = od_type;
  selects->order_by.order_info_num++;
}

void selects_append_conditions(Selects *selects, Condition conditions[], size_t condition_num)
{
  assert(condition_num <= sizeof(selects->conditions) / sizeof(selects->conditions[0]));
  for (size_t i = 0; i < condition_num; i++) {
    selects->conditions[i] = conditions[i];
  }
  selects->condition_num = condition_num;
}

void relation_destroy(Relation* relation) {
  if (relation->name != nullptr) {
    free(relation->name);
  }
  if (relation->alias != nullptr) {
    free(relation->alias);
  }
  relation->name = nullptr;
  relation->alias = nullptr;
}

void selects_destroy(Selects *selects)
{
  for (size_t i = 0; i < selects->attr_num; i++) {
    relation_attr_destroy(&selects->attributes[i]);
  }
  selects->attr_num = 0;

  for (size_t i = 0; i < selects->relation_num; i++) {
    relation_destroy(&selects->relations[i]);
  }
  selects->relation_num = 0;

  for (size_t i = 0; i < selects->condition_num; i++) {
    condition_destroy(&selects->conditions[i]);
  }
  selects->condition_num = 0;

  groupby_destroy(&selects->group_by);
  expr_list_destroy(&selects->expr_list);
  orderby_destroy(&selects->order_by);
}

void clear_buffer_expr_cell_list(ExprCellBuffer* exprCellBuffer, int len) {
  for (int i = 0; i < len; ++i) {
    for (int j = 0; j < 3; ++j) {
      if (exprCellBuffer[i].data[j] != nullptr) {
        free(exprCellBuffer[i].data[j]);
        exprCellBuffer[i].data[j] = nullptr;
      }
    }
    exprCellBuffer[i].type = 0;
    exprCellBuffer[i].value_pos = 0;
  }
}

void inserts_init(Inserts *inserts, const char *relation_name, Value values[], size_t value_num)
{
  assert(value_num <= sizeof(inserts->values) / sizeof(inserts->values[0]));

  inserts->relation_name = strdup(relation_name);
  for (size_t i = 0; i < value_num; i++) {
    inserts->values[i] = values[i];
  }
  inserts->value_num = value_num;
}
void inserts_destroy(Inserts *inserts)
{
  free(inserts->relation_name);
  inserts->relation_name = nullptr;

  for (size_t i = 0; i < inserts->value_num; i++) {
    value_destroy(&inserts->values[i]);
  }
  inserts->value_num = 0;
}

void deletes_init_relation(Deletes *deletes, const char *relation_name)
{
  deletes->relation_name = strdup(relation_name);
}

void deletes_set_conditions(Deletes *deletes, Condition conditions[], size_t condition_num)
{
  assert(condition_num <= sizeof(deletes->conditions) / sizeof(deletes->conditions[0]));
  for (size_t i = 0; i < condition_num; i++) {
    deletes->conditions[i] = conditions[i];
  }
  deletes->condition_num = condition_num;
}
void deletes_destroy(Deletes *deletes)
{
  for (size_t i = 0; i < deletes->condition_num; i++) {
    condition_destroy(&deletes->conditions[i]);
  }
  deletes->condition_num = 0;
  free(deletes->relation_name);
  deletes->relation_name = nullptr;
}

void updates_init(Updates *updates, const char *relation_name, const char *attribute_name, Value *value,
    Condition conditions[], size_t condition_num)
{
  updates->relation_name = strdup(relation_name);
  updates->attribute_name = strdup(attribute_name);
  updates->value = *value;

  assert(condition_num <= sizeof(updates->conditions) / sizeof(updates->conditions[0]));
  for (size_t i = 0; i < condition_num; i++) {
    updates->conditions[i] = conditions[i];
  }
  updates->condition_num = condition_num;
}

void updates_destroy(Updates *updates)
{
  free(updates->relation_name);
  free(updates->attribute_name);
  updates->relation_name = nullptr;
  updates->attribute_name = nullptr;

  value_destroy(&updates->value);

  for (size_t i = 0; i < updates->condition_num; i++) {
    condition_destroy(&updates->conditions[i]);
  }
  updates->condition_num = 0;
}

void create_table_append_attribute(CreateTable *create_table, AttrInfo *attr_info)
{
  create_table->attributes[create_table->attribute_count++] = *attr_info;
}

void create_table_init_name(CreateTable *create_table, const char *relation_name)
{
  create_table->relation_name = strdup(relation_name);
}

void create_table_destroy(CreateTable *create_table)
{
  for (size_t i = 0; i < create_table->attribute_count; i++) {
    attr_info_destroy(&create_table->attributes[i]);
  }
  create_table->attribute_count = 0;
  free(create_table->relation_name);
  create_table->relation_name = nullptr;
}

void drop_table_init(DropTable *drop_table, const char *relation_name)
{
  drop_table->relation_name = strdup(relation_name);
}

void drop_table_destroy(DropTable *drop_table)
{
  free(drop_table->relation_name);
  drop_table->relation_name = nullptr;
}

void create_index_init(
    CreateIndex *create_index, const char *index_name, const char *relation_name, const char *attr_name)
{
  create_index->index_name = strdup(index_name);
  create_index->relation_name = strdup(relation_name);
  create_index->attribute_name = strdup(attr_name);
}

void create_index_destroy(CreateIndex *create_index)
{
  free(create_index->index_name);
  free(create_index->relation_name);
  free(create_index->attribute_name);

  create_index->index_name = nullptr;
  create_index->relation_name = nullptr;
  create_index->attribute_name = nullptr;
}

void drop_index_init(DropIndex *drop_index, const char *index_name)
{
  drop_index->index_name = strdup(index_name);
}

void drop_index_destroy(DropIndex *drop_index)
{
  free((char *)drop_index->index_name);
  drop_index->index_name = nullptr;
}

void show_index_init(ShowIndex *show_index, const char* relation_name)
{
  show_index->relation_name = strdup(relation_name);
}

void show_index_destroy(ShowIndex *show_index)
{
  free((char *)show_index->relation_name);
  show_index->relation_name = nullptr;
}


void desc_table_init(DescTable *desc_table, const char *relation_name)
{
  desc_table->relation_name = strdup(relation_name);
}

void desc_table_destroy(DescTable *desc_table)
{
  free((char *)desc_table->relation_name);
  desc_table->relation_name = nullptr;
}

void load_data_init(LoadData *load_data, const char *relation_name, const char *file_name)
{
  load_data->relation_name = strdup(relation_name);

  if (file_name[0] == '\'' || file_name[0] == '\"') {
    file_name++;
  }
  char *dup_file_name = strdup(file_name);
  int len = strlen(dup_file_name);
  if (dup_file_name[len - 1] == '\'' || dup_file_name[len - 1] == '\"') {
    dup_file_name[len - 1] = 0;
  }
  load_data->file_name = dup_file_name;
}

void load_data_destroy(LoadData *load_data)
{
  free((char *)load_data->relation_name);
  free((char *)load_data->file_name);
  load_data->relation_name = nullptr;
  load_data->file_name = nullptr;
}

void query_init(Query *query)
{
  query->flag = SCF_ERROR;
  memset(&query->sstr, 0, sizeof(query->sstr));
}

Query *query_create()
{
  Query *query = (Query *)malloc(sizeof(Query));
  if (nullptr == query) {
    LOG_ERROR("Failed to alloc memroy for query. size=%ld", sizeof(Query));
    return nullptr;
  }

  query_init(query);
  return query;
}

void query_reset(Query *query)
{
  switch (query->flag) {
    case SCF_SELECT: {
      selects_destroy(&query->sstr.selection);
    } break;
    case SCF_INSERT: {
      inserts_destroy(&query->sstr.insertion);
    } break;
    case SCF_DELETE: {
      deletes_destroy(&query->sstr.deletion);
    } break;
    case SCF_UPDATE: {
      updates_destroy(&query->sstr.update);
    } break;
    case SCF_CREATE_TABLE: {
      create_table_destroy(&query->sstr.create_table);
    } break;
    case SCF_DROP_TABLE: {
      drop_table_destroy(&query->sstr.drop_table);
    } break;
    case SCF_CREATE_INDEX: {
      create_index_destroy(&query->sstr.create_index);
    } break;
    case SCF_DROP_INDEX: {
      drop_index_destroy(&query->sstr.drop_index);
    } break;
    case SCF_SHOW_INDEX: {
      show_index_destroy(&query->sstr.show_index);
    } break;
    case SCF_SYNC: {

    } break;
    case SCF_SHOW_TABLES:
      break;

    case SCF_DESC_TABLE: {
      desc_table_destroy(&query->sstr.desc_table);
    } break;

    case SCF_LOAD_DATA: {
      load_data_destroy(&query->sstr.load_data);
    } break;
    case SCF_CLOG_SYNC:
    case SCF_BEGIN:
    case SCF_COMMIT:
    case SCF_ROLLBACK:
    case SCF_HELP:
    case SCF_EXIT:
    case SCF_ERROR:
      break;
  }
}

void query_destroy(Query *query)
{
  query_reset(query);
  free(query);
}
#ifdef __cplusplus
}  // extern "C"
#endif  // __cplusplus

////////////////////////////////////////////////////////////////////////////////

extern "C" int sql_parse(const char *st, Query *sqls);

RC parse(const char *st, Query *sqln)
{
  sql_parse(st, sqln);

  if (sqln->flag == SCF_ERROR)
    return SQL_SYNTAX;
  else
    return SUCCESS;
}