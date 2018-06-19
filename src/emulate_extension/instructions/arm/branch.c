//
// Created by qs4617 on 02/06/18.
//

#include <assert.h>
#include "branch.h"
#include "../../util/cpsr_util.h"
#include "../../util/logger.h"

enum ExecutionExitCode execute_instruction_branch(struct BranchInstruction instruction) {
    if (!should_execute(instruction.cond)) {
        if(get_word_from_register(PC_ADDRESS) - 4 == 0x10184){
            enable_log();
        }
        return DIDNT_EXECUTE;
    }

    if (instruction.linkBit) {

        set_word_in_register(LR_ADDRESS, get_word_from_register(PC_ADDRESS) - 4);

        assert((get_word_from_register(LR_ADDRESS) & 0x2) == 0);

//        add_exception_flag(BRANCH_LINK_EXCEPTION);

    }
    //} else {


    //calculate offset
    int32_t offset = (instruction.offset & 0xffffff) << 2;
    const uint32_t mask = 0x02000000; //bit_25 is sign bit after left shift
    if ((offset & mask) != 0) {
        offset |= 0xfc000000;
    }

    set_word_in_register(PC_ADDRESS, get_word_from_register(PC_ADDRESS) + offset);

    //}

    return BRANCH;
}
