//
// Created by qs4617 on 02/06/18.
//

#include "add_offset_to_stack_pointer.h"
#include "../../state/emulator_state.h"
#include "../../util/common_enums.h"

enum ExecutionExitCode execute_instruction_add_offset_to_stack_pointer(struct AddOffsetToStackPointerInstruction instruction) {
    if (instruction.signFlag) {
        set_word_in_register(PC_ADDRESS, get_word_from_register(PC_ADDRESS) - (instruction.sword7 << 1));
    } else {
        set_word_in_register(PC_ADDRESS, get_word_from_register(PC_ADDRESS) + (instruction.sword7 << 1));
    }
    return OK;
}
