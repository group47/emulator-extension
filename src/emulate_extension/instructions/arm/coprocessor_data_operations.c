//
// Created by qs4617 on 02/06/18.
//

#include <assert.h>
#include <stdio.h>
#include "coprocessor_data_operations.h"
#include "../../util/cpsr_util.h"

enum ExecutionExitCode execute_instruction_coprocessor_data_operations(struct CoprocessorDataOperationsInstruction instruction) {
    if (!should_execute(instruction.cond)) {
        return DIDNT_EXECUTE;
    }

    fprintf(stderr, "Try to execute coprocessor data operations\n");
    fprintf(stderr, "Coprocessor number : %d\n", instruction.CoNumber);
    assert(false);

    // todo: fed the instruction to the coprocessor
    return OK;
}
