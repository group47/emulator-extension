//
// Created by fpn17 on 02/06/18.
//

#include <assert.h>
#include "move_compare_add_subtract.h"
#include "../../util/common_enums.h"
#include "../../state/emulator_state.h"
#include "../../util/cpsr_util.h"
#include "../../util/overflow_util.h"


enum ExecutionExitCode execute_instruction_move_compare_add_subtract(struct MoveCompareAddSubtract instruction) {
    assert(instruction.filler001 == 0b001);
    uint32_t computation_res;
    bool overflow_occurred = false;
    bool borrow_occurred = false;
    switch (instruction.op) {
        case MOV_MOVECOMPAREADDSUBTRACTOPCODE:
            computation_res = instruction.offset8;
            set_word_in_register(instruction.Rd, computation_res);
        case CMP_MOVECOMPAREADDSUBTRACTOPCODE:
        case SUB_MOVECOMPAREADDSUBTRACTOPCODE:
            computation_res = get_word_from_register(instruction.Rd) - instruction.offset8;
            if (does_borrow_occur(get_word_from_register(instruction.Rd), instruction.offset8)) {
                borrow_occurred = true;
            }
            if (instruction.op == SUB_MOVECOMPAREADDSUBTRACTOPCODE) {
                set_word_in_register(instruction.Rd, computation_res);
            }
            break;
        case ADD_MOVECOMPAREADDSUBTRACTOPCODE:
            computation_res = get_word_from_register(instruction.Rd) + instruction.offset8;
            if (does_overflow_occur(get_word_from_register(instruction.Rd), instruction.offset8)) {
                overflow_occurred = true;
            }
            set_word_in_register(instruction.Rd, computation_res);
            break;
        default:
            assert(false);
    }
    high_level_set_CPSR_thumb_move_compare_add_sub(instruction, borrow_occurred, overflow_occurred, computation_res,
                                                   getCPSR().C);
    return OK;
}

