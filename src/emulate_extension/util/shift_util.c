//
// Created by fpn17 on 02/06/18.
//

#include <stdint.h>
#include "shift_util.h"

// adapted from  https://stackoverflow.com/questions/7622/are-the-shift-operators-arithmetic-or-logical-in-c

int32_t arithmetic_right_shift(int32_t x, int32_t n) {
    if (x < 0 && n > 0)
        return x >> n | ~(~0U >> n);
    else
        return x >> n;
}