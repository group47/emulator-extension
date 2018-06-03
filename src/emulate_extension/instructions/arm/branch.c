//
// Created by qs4617 on 02/06/18.
//

#include <assert.h>
#include "branch.h"
#include "../../util/cpsr_util.h"

enum ExecutionExitCode execute_instruction_branch(struct BranchInstruction instruction) {
    if (!should_execute(instruction.cond)) {
        return DIDNT_EXECUTE;
    }

    if (instruction.linkBit) {
        set_word_in_register(PC_ADDRESS, get_word_from_register(PC_ADDRESS) +
                                         (uint32_t) instruction.offset << 2 - 8);
    } else {
        assert(false);
    }

    add_exception_flag(BRANCH_EXCEPTION);
    return BRANCH;
}
