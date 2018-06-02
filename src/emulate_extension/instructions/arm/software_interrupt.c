//
// Created by qs4617 on 02/06/18.
//

#include "software_interrupt.h"
#include "../../util/cpsr_util.h"

enum ExecutionExitCode execute_instruction_software_interrupt(struct SoftWareInterruptInstruction instruction) {
    if (!should_execute(instruction.cond)) {
        return DIDNT_EXECUTE;
    }

    add_exception_flag(SOFTWARE_INTERRUPT);

    return OK;
}
