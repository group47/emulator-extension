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

bool does_signed_overflow(int32_t a, int32_t b) {
    //todo this only applies to addition?
    if (a > 0 && b > 0) {
        return a + b < 0;
    } else if (a < 0 && b < 0) {
        return a + b > 0;
    } else {
        return false;
    }
}

