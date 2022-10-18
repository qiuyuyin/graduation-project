//
// Created by johnsonlee on 10/18/22.
//

#include "typecaster.h"
#include "common/log/log.h"
#include "storage/common/field_meta.h"
namespace cast {
static int s2i(const char *s)
{
  int v = 0;
  sscanf(s, "%d", &v);
  return v;
}

static float s2f(const char *s)
{
  float v = 0.0;
  sscanf(s, "%f", &v);
  return v;
}
static int i2s(char buf[], int i)
{
  snprintf(buf, 20, "%d", i);
}
static float i2f(int i)
{
  return i;
}
static int f2i(float f)
{
  return f + 0.5;
}
};  // namespace cast
static void chars_to_ints(Value *value)
{
  int v = cast::s2i(static_cast<const char *>(value->data));
  value_destroy(value);
  value_init_integer(value, v);
}
static void ints_to_chars(Value *value)
{
  char buf[20];
  cast::i2s(buf, *static_cast<int *>(value->data));
  value_destroy(value);
  value_init_string(value, buf);
}
static void ints_to_floats(Value *value)
{
  float v = cast::i2f(*static_cast<int *>(value->data));
  value_destroy(value);
  value_init_float(value, v);
}
static void floats_to_ints(Value *value)
{
  int v = cast::f2i(*static_cast<float *>(value->data));
  value_destroy(value);
  value_init_integer(value, v);
}
static void chars_to_floats(Value *value)
{
  float v = cast::s2f(static_cast<const char *>(value->data));
  value_destroy(value);
  value_init_float(value, v);
}
TypecastTable Typecaster::available_cast_ = {
    {{AttrType::CHARS, AttrType::INTS}, chars_to_ints},
    {{AttrType::INTS, AttrType::CHARS}, ints_to_chars},
    {{AttrType::INTS, AttrType::FLOATS}, ints_to_floats},
    {{AttrType::FLOATS, AttrType::INTS}, floats_to_ints},
    {{AttrType::CHARS, AttrType::FLOATS}, chars_to_floats},
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
