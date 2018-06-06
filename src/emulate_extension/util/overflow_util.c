//
// Created by francis on 6/2/18.
//

#include "overflow_util.h"

bool does_overflow_occur(uint32_t a, uint32_t b) {
  return ~a < b;

}


bool does_borrow_occur(uint32_t a, uint32_t b) {
  return a < b;
}
