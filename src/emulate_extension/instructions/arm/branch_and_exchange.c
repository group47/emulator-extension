//
// Created by qs4617 on 02/06/18.
//

#include <assert.h>
#include "branch_and_exchange.h"
#include "../../util/cpsr_util.h"


enum ExecutionExitCode execute_instruction_branch_and_exchange_instruction(struct BranchAndExchangeInstruction instruction) {
    if (!should_execute(instruction.cond)) {
        return DIDNT_EXECUTE;
    }

    assert(instruction.Rn != PC_ADDRESS);

    // todo: the instruction will cause a pipeline flush




}
