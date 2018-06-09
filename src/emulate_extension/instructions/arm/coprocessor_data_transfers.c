//
// Created by qs4617 on 02/06/18.
//

#include "coprocessor_data_transfers.h"
#include "../../util/cpsr_util.h"


enum ExecutionExitCode
execute_instruction_coprocessor_data_transfers(struct CoprocessorDataTransfersInstruction instruction) {
    if (!should_execute(instruction.cond)) {
        return DIDNT_EXECUTE;
    }

    return OK;
}
