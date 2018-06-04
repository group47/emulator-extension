//
// Created by qs4617 on 03/06/18.
//

#include <assert.h>
#include "exception.h"
#include "emulator_state.h"

/*
 * MONSTER COMMENT
 *
 *
 *
 When handling an exception, the ARM7TDMI:
1 Preserves the address of the next instruction in the appropriate Link Register.
If the exception has been entered from ARM state, then the address of the
next instruction is copied into the Link Register (that is, current PC + 4 or PC
+ 8 depending on the exception. See òTable 3-2: Exception entry/exit on
page 3-11 for details). If the exception has been entered from THUMB state,
then the value written into the Link Register is the current PC offset by a value
such that the program resumes from the correct place on return from the
exception. This means that the exception handler need not determine which
state the exception was entered from. For example, in the case of SWI, MOVS
PC, R14_svc will always return to the next instruction regardless of whether
the SWI was executed in ARM or THUMB state.
2 Copies the CPSR into the appropriate SPSR
3 Forces the CPSR mode bits to a value which depends on the exception
4 Forces the PC to fetch the next instruction from the relevant exception vector
It may also set the interrupt disable flags to prevent otherwise unmanageable nestings
of exceptions.
If the processor is in THUMB state when an exception occurs, it will automatically
switch into ARM state when the PC is loaded with the exception vector address.
 *
 *
 *
 * */
// keeps calling exception_handler until there are no exceptions
// todo: determine which exception to handle externally
void handle_exception() {
    int offset = 0;
    enum OperatingMode newMode;

    struct CPSR_Struct oldCPSR = getCPSR();

    oldCPSR.F = 1;//todo check
    oldCPSR.I = 1;

    if (has_exception_flag(RESET)) {
        assert(false);
    } else if (has_exception_flag(DATA_ABORT)) {
        newMode = abt;
        offset = 8;
//        if (get_mode() == ARM) {
//            switch (get_decoded_arm()) {
//                case ARM_SINGLE_DATA_TRANSFER :
//                    break;
//                case ARM_SINGLE_DATA_SWAP :
//                    break;
//                case ARM_BLOCK_DATA_TRANSFER:
//                    break;
//
//            }
//        }

    } else if (has_exception_flag(FIQ)) {
        assert(get_operating_mode() != usr);
        newMode = fiq;
        offset = 4;
        oldCPSR.F = 0;
        setCPSR(oldCPSR);
    } else if (has_exception_flag(IRQ)) {
        assert(get_operating_mode() != usr);
        newMode = irq;
        offset = 4;
        oldCPSR.I = 0;
        setCPSR(oldCPSR);
    } else if (has_exception_flag(PREFETCH_ABORT)) {
        newMode = abt;
        offset = 4;
    } else if (has_exception_flag(UNDEFINED)) {
        newMode = und;
        offset = get_mode() == ARM ? 4 : 2;
    } else if (has_exception_flag(SOFTWARE_INTERRUPT)) {
        newMode = svc;
        offset = get_mode() == ARM ? 4 : 2;
    } else if (has_exception_flag(BRANCH_EXCEPTION)) {
        //todo
    }


    setSPSR(getCPSR());


}

bool has_exceptions(){
    return get_exception_flags() != 0;
}