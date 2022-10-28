//
// Created by sheep on 2022/10/22.
//

#include "sort_operator.h"

RC SortOperator::open(){
  if (children_.size() != 1) {
    LOG_WARN("sort operator must has one child");
    return RC::INTERNAL;
  }
  RC rc;
  if ((rc = children_[0]->open()) != SUCCESS) {
    LOG_WARN("sort operator's children open error");
    return rc;
  }

  while ((rc = children_[0]->next()) == SUCCESS) {
    RowTuple *trans = dynamic_cast<RowTuple *>(children_[0]->current_tuple());
    VTuple *temp = new VTuple;
    temp->append_row_tuple(*trans);
    tuple_set.push_back(temp);
  }
  if (rc == RECORD_EOF) {
    tupleSort();
    res_iter_type = BEFORE_BEGIN;
    rc = SUCCESS;
  }
  return rc;
}

RC SortOperator::next(){
  RC rc = SUCCESS;
  if (res_iter_type == BEFORE_BEGIN){
    tuple_index = 0;
    res_iter_type = ON_WAY;
    return rc;
  }

  if(tuple_index == tuple_set.size()){
    return RECORD_EOF;
  }
  tuple_index++;
}

RC SortOperator::close()
{
  RC rc;
  if ((rc = children_[0]->close()) != SUCCESS) {
    LOG_WARN("sort operator's children close error");
    return rc;
  }
  return SUCCESS;
}

void SortOperator::tupleSort()
{
  vector<Tuple4Sort> sort_tuple_set;
  for(auto it:tuple_set){
    Tuple4Sort tmp;
    tmp.tuple_data = *it;
    tmp.odb_fields.assign(orderby_fields_.begin(),orderby_fields_.end());
    sort_tuple_set.push_back(tmp);
  }
  sort(sort_tuple_set.begin(),sort_tuple_set.end(), compare_for_sort);
  vector<VTuple *> res;
  for(auto it:sort_tuple_set){
    res.push_back(&it.tuple_data  );
  }
  tuple_set.swap(res);
}


bool compare_for_sort(Tuple4Sort arg1,Tuple4Sort arg2){
  for(auto iter : arg1.odb_fields){
    int order_flag = (iter.od_type == ASC_ORDER? 1:-1);
    TupleCell tmp_arg1_cell,tmp_arg2_cell;
    if (arg1.tuple_data.find_cell(*iter.orderby_field,tmp_arg1_cell) != SUCCESS) {
      LOG_WARN("fail to get cell");
      return 0;
    }
    if (arg2.tuple_data.find_cell(*iter.orderby_field,tmp_arg2_cell) != SUCCESS) {
      LOG_WARN("fail to get cell");
      return 0;
    }
    order_flag *=tmp_arg1_cell.compare(tmp_arg2_cell);
    if(tmp_arg1_cell.compare(tmp_arg2_cell) == 0){
      continue ;
    }else{
      return order_flag<0;
    }
  }
  return 0;
}