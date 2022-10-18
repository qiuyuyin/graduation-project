//
// Created by johnsonlee on 10/18/22.
//

#ifndef MINIDB_TYPECASTER_H
#define MINIDB_TYPECASTER_H

#include <map>
#include "rc.h"
#include "sql/parser/parse_defs.h"
#include "sql/expr/expression.h"
using CastPair = std::pair<AttrType, AttrType>;
using Caster = void (*)(Value *);
using TypecastTable = std::map<CastPair, Caster>;

class Typecaster {
public:
  static RC attr_cast(Value *value, AttrType target_type);
  static RC expr_cast(Expression *&left, AttrType left_attr_type, Expression *&right, AttrType right_attr_type);

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

private:
  static TypecastTable available_cast_;
};

#endif  // MINIDB_TYPECASTER_H
