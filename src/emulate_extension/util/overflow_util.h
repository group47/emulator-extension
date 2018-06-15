//
// Created by francis on 6/2/18.
//

#ifndef SRC_OVERFLOW_UTIL_H
#define SRC_OVERFLOW_UTIL_H

#include <stdint.h>
#include <stdbool.h>

bool does_overflow_occur(uint32_t a, uint32_t b);

bool does_borrow_occur(uint32_t a, uint32_t b);

bool does_signed_overflow(int32_t a, int32_t b);

#endif //SRC_OVERFLOW_UTIL_H
