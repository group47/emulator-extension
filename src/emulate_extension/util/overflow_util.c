//
// Created by francis on 6/2/18.
//

#include "overflow_util.h"

bool does_overflow_occur(uint32_t a, uint32_t b) {
  uint64_t overflowable_res = ((uint64_t)a) + ((uint64_t)b);
  return overflowable_res & 0x100000000;//todo reciever type?
}


bool does_borrow_occur(uint32_t a, uint32_t b) {
  return ((int64_t)a - (int64_t)b) < 0;
}
