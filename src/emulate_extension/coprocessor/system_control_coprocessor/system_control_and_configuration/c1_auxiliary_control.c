//
// Created by qs4617 on 07/06/18.
//

#include <assert.h>
#include "../../../instructions/arm/coprocessor_register_transfer.h"
#include "../../../state/emulator_state.h"
#include "c1_auxiliary_control.h"

enum ExecutionExitCode execute_co_auxiliary_control_register(struct CoprocessorRegisterTransferInstruction instruction) {
    /*
    if (instruction.loadStore == LOAD) {
        set_word_in_register(instruction.Rd, *((uint32_t*) &get_system_control_coprocessor()->c1_auxiliary_control_register));
    } else {
        Word val = get_word_from_register(instruction.Rd);
        get_system_control_coprocessor()->c1_auxiliary_control_register =
                *((struct C1_auxiliary_control_register*) &val);
    }
    return OK;
     */
    assert(false);
}
