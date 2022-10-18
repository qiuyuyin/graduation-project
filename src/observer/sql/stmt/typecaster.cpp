//
// Created by johnsonlee on 10/18/22.
//

#include "typecaster.h"
#include "common/log/log.h"
#include "storage/common/field_meta.h"
static void chars_to_ints(Value *value)
{
  int v = Typecaster::s2i(static_cast<const char *>(value->data));
  value_destroy(value);
  value_init_integer(value, v);
}
static void ints_to_chars(Value *value)
{
  char buf[20];
  Typecaster::i2s(buf, *static_cast<int *>(value->data));
  value_destroy(value);
  value_init_string(value, buf);
}
static void ints_to_floats(Value *value)
{
  float v = Typecaster::i2f(*static_cast<int *>(value->data));
  value_destroy(value);
  value_init_float(value, v);
}
static void floats_to_ints(Value *value)
{
  int v = Typecaster::f2i(*static_cast<float *>(value->data));
  value_destroy(value);
  value_init_integer(value, v);
}
static void chars_to_floats(Value *value)
{
  float v = Typecaster::s2f(static_cast<const char *>(value->data));
  value_destroy(value);
  value_init_float(value, v);
}
static void floats_to_chars(Value *value)
{
  char buf[20];
  Typecaster::f2s(buf, *static_cast<float *>(value->data));
  value_destroy(value);
  value_init_string(value, buf);
}
TypecastTable Typecaster::available_cast_ = {
    {{AttrType::CHARS, AttrType::INTS}, chars_to_ints},
    {{AttrType::INTS, AttrType::CHARS}, ints_to_chars},
    {{AttrType::INTS, AttrType::FLOATS}, ints_to_floats},
    {{AttrType::FLOATS, AttrType::INTS}, floats_to_ints},
    {{AttrType::CHARS, AttrType::FLOATS}, chars_to_floats},
    {{AttrType::FLOATS, AttrType::CHARS}, floats_to_chars},
};

RC Typecaster::attr_cast(Value *value, AttrType target_type)
{
  auto foo = chars_to_ints;
  if (value->type == target_type) {
    return RC::SUCCESS;
  }
  if (!available_cast_.count({value->type, target_type})) {
    LOG_ERROR("Typecast error");
    return RC::TYPECAST;
  }
  auto caster = available_cast_[{value->type, target_type}];
  caster(value);
  return RC::SUCCESS;
}
RC Typecaster::expr_cast(Expression *&left,AttrType left_attr_type, Expression *&right, AttrType right_attr_type)
{
  if (left_attr_type == right_attr_type){
    return RC::SUCCESS;
  }
}
