//
// Created by qs4617 on 07/06/18.
//

#include "c0_id_code.h"
#include "../../../state/emulator_state.h"

enum ExecutionExitCode execute_co_main_id_register(struct CoprocessorRegisterTransferInstruction instruction) {
    // todo: results of attempted access for each mode
    set_word_in_register(instruction.Rd, );
}
