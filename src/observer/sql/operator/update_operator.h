//
// Created by sheep on 2022/10/17.
//


#pragma once

#include "sql/operator/operator.h"
#include "rc.h"

class UpdateStmt;

class UpdateOperator : public Operator{
public:
  UpdateOperator(UpdateStmt *update_stmt)
    : update_stmt_(update_stmt)
  {}
  virtual ~UpdateOperator() = default;

  RC open() override;
  RC next() override;
  RC close() override;

  Tuple * current_tuple() override {
    return nullptr;
  }

private:
  UpdateStmt *update_stmt_ = nullptr;
};