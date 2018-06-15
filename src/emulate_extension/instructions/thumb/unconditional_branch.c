//
// Created by mhl1817 on 02/06/18.
//

#include <assert.h>
#include "unconditional_branch.h"
#include "../../state/emulator_state.h"

enum ExecutionExitCode
execute_instruction_unconditional_branch(const struct UnconditionalBranchInstruction instruction) {

    assert(instruction.filler11100 == 0b11100);

    int16_t offset = (int16_t) (instruction.offset * 2);

    set_word_in_register(PC_ADDRESS, get_word_from_register(PC_ADDRESS) - 4 + offset);

//  add_exception_flag(BRANCH_LINK_EXCEPTION);

    return BRANCH;

}
