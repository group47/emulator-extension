//
// Created by fpn17 on 02/06/18.
//

#include <assert.h>
#include <stdio.h>
#include "coprocessor_register_transfer.h"
#include "../../util/entry_point.h"
#include "../../util/cpsr_util.h"

enum ExecutionExitCode execute_copprocessor_register_transfer(struct CoProcessorRegisterTransfer instruction) {
    if (!should_execute(instruction.cond)) {
        return DIDNT_EXECUTE;
    }

    fprintf(get_logfile(), "Coprocessor CP: %d\n", instruction.CP);
    fprintf(get_logfile(), "Coprocessor CPNum: %d\n", instruction.CPNum);
    fprintf(get_logfile(), "Coprocessor CPOpc: %d\n", instruction.CPOpc);
    fprintf(get_logfile(), "Coprocessor CRm: %d\n", instruction.CRm);
    fprintf(get_logfile(), "Coprocessor CRn: %d\n", instruction.CRn);
    fprintf(get_logfile(), "Coprocessor load/store bit: %d\n", instruction.loadStore);
    fprintf(get_logfile(), "Coprocessor Rd: %d\n", instruction.Rd);

    assert(false);
    return OK;
}