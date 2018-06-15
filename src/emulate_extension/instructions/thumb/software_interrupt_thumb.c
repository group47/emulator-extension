//
// Created by fpn17 on 02/06/18.
//

#include <stdint.h>
#include <assert.h>
#include "software_interrupt_thumb.h"
#include "../../state/emulator_state.h"

enum ExecutionExitCode execute_instruction_thumb_software_interrupt(struct SoftwareInterruptThumb instruction) {
    assert (instruction.filler11011111 == 0b11011111);
    add_exception_flag(SOFTWARE_INTERRUPT);
    return OK;
}