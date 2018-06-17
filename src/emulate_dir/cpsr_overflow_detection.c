//
// Created by francis on 5/24/18.
//

#include <stdbool.h>
#include <stdint.h>
#include "cpsr_overflow_detection.h"

bool does_overflow_occur(uint32_t a, uint32_t b) {
    uint64_t overflowable_res = ((uint64_t) a) + ((uint64_t) b);
    return overflowable_res & 0x100000000;
}


bool does_borrow_occur(uint32_t a, uint32_t b) {
    return ((int64_t) a - (int64_t) b) < 0;
}
