//
// Created by Joenhle on 2022/10/21.
//


#include "sql/operator/join_operator.h"

RC JoinOperator::open()
{
  if (children_.size() != 2) {
    LOG_WARN("join_operator must has two child");
    return RC::INTERNAL;
  }
  RC rc;
  if ((rc = children_[0]->open()) != SUCCESS || (rc = children_[1]->open()) != SUCCESS) {
    LOG_WARN("join operator's children open error");
    return rc;
  }
  if ((rc = children_[0]->next()) == SUCCESS) {
    round_done_ = false;
    outer_tuple_ = VTuple(*children_[0]->current_tuple());
  }
  if (rc == RECORD_EOF) {
    return SUCCESS;
  }
  return rc;
}

RC JoinOperator::close()
{
  RC rc;
  if ((rc = children_[0]->close()) != SUCCESS || (rc = children_[1]->close()) != SUCCESS) {
    LOG_WARN("join operator's children close error");
    return rc;
  }
  return SUCCESS;
}

RC JoinOperator::next()
{
  RC rc;
  while (!round_done_) {
    while ((rc = children_[1]->next()) == SUCCESS) {
      VTuple inner = VTuple(*children_[1]->current_tuple());
      VTuple res;
      if((rc = outer_tuple_.merge(inner, res)) != SUCCESS) {
        return rc;
      }
      tuple_ = res;
      return rc;
    }
    if (rc == RECORD_EOF) {
      if((rc = children_[1]->open()) != SUCCESS) {
        return rc;
      }
    } else {
      return rc;
    }
    if ((rc = children_[0]->next()) == SUCCESS) {
      outer_tuple_ = VTuple(*children_[0]->current_tuple());
    }
    if (rc == RECORD_EOF) {
      round_done_ = true;
    } else {
      return rc;
    }
  }
  return rc;
}



