//
// Created by francis on 5/24/18.
//

#include <stdbool.h>
#include <elf.h>
#include "cpsr_overflow_detection.h"


bool does_overflow_occur(uint32_t a, uint32_t b) {
  uint64_t overflowable_res = ((uint64_t)a) + ((uint64_t)b);
  if (overflowable_res < a) {
      return true;
  }
  if(overflowable_res & 0b100000000000000000000000000000000)//todo this constant is ridiculous
      return true;
  return false;
}


bool does_borrow_occur(uint32_t a, uint32_t b) {
  const int64_t res = a - b;
  return res < 0;
}
