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

    struct CPSR_Struct oldCPSR = getCPSR();

    oldCPSR.F = 1;//todo check
    oldCPSR.I = 1;

    if(has_exception_flag(RESET)) {
        newMode = svc;
    }
    else if(has_exception_flag(DATA_ABORT)){
        newMode = abt;
        offset = 8;

    }
    else if(has_exception_flag(FIQ)){
        assert(get_mode() != usr);
        newMode = fiq;
        offset = 4;
        oldCPSR.F = 0;
        setCPSR(oldCPSR);
    }
    else if(has_exception_flag(IRQ)){
        assert(get_mode() != usr);
        newMode = irq;
        offset = 4;
        oldCPSR.I = 0;
        setCPSR(oldCPSR);
    } else if(has_exception_flag(PREFETCH_ABORT)){
        newMode = abt;
        offset = 4;
    } else if(has_exception_flag(UNDEFINED)){
        newMode = und;
        offset = get_mode() == ARM ? 4 : 2;
    } else if(has_exception_flag(SOFTWARE_INTERRUPT)){
        newMode = svc;
        offset = get_mode() == ARM ? 4 : 2;
    }
    else if(has_exception_flag(BRANCH_EXCEPTION)){
        //todo
    }



    setSPSR(state.CPSR, *get_SPSR_by_mode());






}