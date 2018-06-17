//
// Created by francis on 5/24/18.
//

#ifndef EMULATE_CPSR_OVERFLOW_DETECTION_H
#define EMULATE_CPSR_OVERFLOW_DETECTION_H

#include <stdint.h>
#include <stdbool.h>

bool does_overflow_occur(uint32_t a, uint32_t b);

bool does_borrow_occur(uint32_t a, uint32_t b);

#endif //EMULATE_CPSR_OVERFLOW_DETECTION_H
