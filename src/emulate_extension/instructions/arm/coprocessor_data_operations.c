//
// Created by qs4617 on 02/06/18.
//

#include <assert.h>
#include "coprocessor_data_operations.h"
#include "../../util/cpsr_util.h"
#include "../../util/logger.h"

enum ExecutionExitCode
execute_instruction_coprocessor_data_operations(struct CoprocessorDataOperationsInstruction instruction) {
    if (!should_execute(instruction.cond)) {
        return DIDNT_EXECUTE;
    }

    struct LogEntry entry;
    entry.type = COPROCESSOR_DATA_OPERATION_LOG_ENTRY;
    entry.dataOperationsInstruction = instruction;
    add_to_log(entry);
    assert(false);

    // todo: fed the instruction to the coprocessor
    return OK;
}
