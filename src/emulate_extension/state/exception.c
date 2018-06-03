//
// Created by qs4617 on 03/06/18.
//

#include <assert.h>
#include "exception.h"
#include "emulator_state.c"


// keeps calling exception_handler until there are no exceptions
// todo: determine which exception to handle externally
void exception_handler() {
    // todo: preserve processor state
    bool currentInstructionIsBL = false;
    bool currentInstructionIsSWI = false;

    // preserve PC value to the next instruction

    int offset = 0;
    enum OperatingMode newMode;

    enum ExceptionFlag current_exception;

    struct CPSR_Struct oldCPSR = getCPSR();

    switch (current_exception) {
        case RESET:
            newMode = svc;
            break;
        case DATA_ABORT:
            newMode = abt;
            offset = 8;
            break;
        case FIQ:
            assert(get_mode() != usr);
            newMode = fiq;
            offset = 4;
            oldCPSR.F = 0;
            setCPSR(oldCPSR);
            break;
        case IRQ:
            assert(get_mode() != usr);
            newMode = irq;
            offset = 4;
            oldCPSR.I = 0;
            setCPSR(oldCPSR);
            break;
        case PREFETCH_ABORT:
            newMode = abt;
            offset = 4;
            break;
        case UNDEFINED:
            newMode = und;
            offset = get_mode() == ARM ? 4 : 2;
            break;
        case SOFTWARE_INTERRUPT:
            newMode = svc;
            offset = get_mode() == ARM ? 4 : 2;
            break;
    }


    setSPSR(state.CPSR, *get_SPSR_by_mode());






}