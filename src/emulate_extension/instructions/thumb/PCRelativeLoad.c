//
// Created by qs4617 on 02/06/18.
//

#include "PCRelativeLoad.h"
#include "../../state/emulator_state.h"

enum ExecutionExitCode execute_instruction_PCRelativeLoad(struct PCRelativeLoadInstruction instruction) {
    set_word_in_register(PC_ADDRESS, get_word_from_register(PC_ADDRESS)
                                     + ((uint32_t)instruction.word8) << 2);
    return OK;
}
