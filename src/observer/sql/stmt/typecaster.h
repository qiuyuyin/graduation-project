//
// Created by johnsonlee on 10/18/22.
//

#ifndef MINIDB_TYPECASTER_H
#define MINIDB_TYPECASTER_H

#include <map>
#include "rc.h"
#include "sql/parser/parse_defs.h"
using CastPair = std::pair<AttrType, AttrType>;
using Caster = void (*)(Value *);
using TypecastTable = std::map<CastPair, Caster>;

class Typecaster {
public:
  static RC attr_cast(Value *value, AttrType target_type);

private:
  static TypecastTable available_cast_;
};

#endif  // MINIDB_TYPECASTER_H
