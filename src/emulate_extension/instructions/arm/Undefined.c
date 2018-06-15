//
// Created by qs4617 on 02/06/18.
//

#include "Undefined.h"
#include "../../util/cpsr_util.h"

enum ExecutionExitCode execute_instruction_undefined(struct UndefinedInstruction instruction) {
    if (!should_execute(instruction.cond)) {
        return DIDNT_EXECUTE;
    }

    add_exception_flag(UNDEFINED);
    return OK;
}
