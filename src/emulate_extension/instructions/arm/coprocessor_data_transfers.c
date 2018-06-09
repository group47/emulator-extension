//
// Created by qs4617 on 02/06/18.
//

#include <assert.h>
#include <stdio.h>
#include "coprocessor_data_transfers.h"
#include "../../util/cpsr_util.h"
#include "../../util/entry_point.h"


enum ExecutionExitCode
execute_instruction_coprocessor_data_transfers(struct CoprocessorDataTransfersInstruction instruction) {
    if (!should_execute(instruction.cond)) {
        return DIDNT_EXECUTE;
    }

    fprintf(get_logfile(), "Coprocesor number %d\n", instruction.CoNumber);
    fprintf(get_logfile(), "Coprocesor base register %d\n", instruction.baseRegister);
    fprintf(get_logfile(), "Coprocesor source destination register %d\n", instruction.CoSourceDestinationRegister);
    fprintf(get_logfile(), "Coprocesor load store bit %d\n", instruction.loadStoreBit);
    fprintf(get_logfile(), "Coprocesor offset %d\n", instruction.offset);
    fprintf(get_logfile(), "Coprocesor pre post indexing %d\n", instruction.prePostIndexingBit);
    fprintf(get_logfile(), "Coprocesor transfer length %d\n", instruction.transferLength);
    fprintf(get_logfile(), "Coprocesor up down bit %d\n", instruction.upDownBit);
    fprintf(get_logfile(), "Coprocesor write back bit %d\n", instruction.writeBackBit);


    assert(false);
    return OK;
}
