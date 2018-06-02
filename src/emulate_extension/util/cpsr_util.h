//
// Created by francis on 6/2/18.
//

#ifndef SRC_CPSR_UTIL_H
#define SRC_CPSR_UTIL_H

#include <stdbool.h>
#include "../state/emulator_state.h"
#include "../util/common_enums.h"
#include "../instructions/arm/data_processing.h"
bool should_execute(enum Cond cond);

void high_level_set_CPSR(struct DataProcessingInstruction instruction, bool borrow_occurred, bool overflow_occurred, uint32_t computation_res,
    uint32_t shiftCarryOut);

#endif //SRC_CPSR_UTIL_H
