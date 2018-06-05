//
// Created by francis on 6/2/18.
//

#ifndef SRC_CPSR_UTIL_H
#define SRC_CPSR_UTIL_H

#include <stdbool.h>
#include "../state/emulator_state.h"
#include "../instructions/arm/data_processing.h"
#include "../instructions/thumb/move_compare_add_subtract.h"

bool should_execute(enum Cond cond);

void high_level_set_CPSR_thumb_move_compare_add_sub(struct MoveCompareAddSubtract subtract, bool occurred,
                                                    bool overflow_occurred, uint32_t res, bool carry_out);

void high_level_set_CPSR_data_processing(const struct DataProcessingInstruction instruction,
                                         const bool borrow,
                                         const bool overflow,
                                         const uint32_t computation_res,
                                         const bool shiftCarryOut);

void high_level_set_CPSR(bool set_condition_codes,bool is_arithmetic,bool is_add,bool is_logical, bool borrow_occurred, bool overflow_occurred, uint32_t computation_res,
    bool shiftCarryOut);
bool is_logical(enum OpCode code);
bool is_arithmetic(enum OpCode code);

#endif //SRC_CPSR_UTIL_H
