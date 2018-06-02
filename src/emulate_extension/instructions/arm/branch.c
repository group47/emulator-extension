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
        set_word_in_register(PC_REGISTER, get_word_from_register(PC_REGISTER) +
                                         (uint32_t) instruction.offset << 2);
    } else {
        assert(false);
    }

    return OK;
}
