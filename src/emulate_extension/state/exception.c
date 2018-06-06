//
// Created by qs4617 on 03/06/18.
//

#include <assert.h>
#include "exception.h"
#include "emulator_state.h"

/*
 * from the spec
 *
 *
 *
 When handling an exception:
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
void handle_data_abort(struct CPSR_Struct oldcpsr);

void handle_fiq(struct CPSR_Struct oldcpsr);

void handle_irq(struct CPSR_Struct oldcpsr);

void handle_prefetch_abort(struct CPSR_Struct oldcpsr);

void handle_undefined(struct CPSR_Struct oldcpsr);

void handle_software_interrupt(struct CPSR_Struct oldcpsr);

void handle_branch(struct CPSR_Struct oldcpsr);

// keeps calling exception_handler until there are no exceptions
// todo: determine which exception to handle externally
void handle_exception() {

    struct CPSR_Struct oldCPSR = getCPSR();

    if (has_exception_flag(RESET)) {
        assert(false);
    } else if (has_exception_flag(DATA_ABORT)) {
        handle_data_abort(oldCPSR);
    } else if (has_exception_flag(FIQ)) {
        assert(get_operating_mode() != usr);
        handle_fiq(oldCPSR);
    } else if (has_exception_flag(IRQ)) {
        assert(get_operating_mode() != usr);
        handle_irq(oldCPSR);
    } else if (has_exception_flag(PREFETCH_ABORT)) {
        handle_prefetch_abort(oldCPSR);
    } else if (has_exception_flag(UNDEFINED)) {
        handle_undefined(oldCPSR);
    } else if (has_exception_flag(SOFTWARE_INTERRUPT)) {
        handle_software_interrupt(oldCPSR);
    } else if (has_exception_flag(BRANCH_LINK_EXCEPTION)) {
        handle_branch(oldCPSR);
    }


//    setSPSR(getCPSR(oldCPSR));


}


/**
 * from spec table 3-2:
 * BL MOV PC, R14 PC + 4 PC + 2
 * Where PC is the address of the BL/SWI/Undefined Instruction fetch which had
the prefetch abort.
 * @param oldcpsr
 */
void handle_branch(struct CPSR_Struct oldcpsr) {
    if (get_mode() == ARM) {
        set_word_in_register(LR_ADDRESS, get_word_from_register(PC_ADDRESS) + 4);
    } else if (get_mode() == THUMB) {
        set_word_in_register(LR_ADDRESS, get_word_from_register(PC_ADDRESS) + 2);
    }


}

/**
 * MOVS PC, R14_svc PC + 4 PC + 2
 * @param oldcpsr
 */
void handle_software_interrupt(struct CPSR_Struct oldcpsr) {
    if (get_mode() == ARM) {
        set_word_in_register(LR_ADDRESS, get_word_from_register(PC_ADDRESS) + 4);
    } else if (get_mode() == THUMB) {
        set_word_in_register(LR_ADDRESS, get_word_from_register(PC_ADDRESS) + 2);
    }
}

void handle_undefined(struct CPSR_Struct oldcpsr) {

}

void handle_prefetch_abort(struct CPSR_Struct oldcpsr) {

}

void handle_irq(struct CPSR_Struct oldcpsr) {

}

void handle_fiq(struct CPSR_Struct oldcpsr) {

}

void handle_data_abort(struct CPSR_Struct oldcpsr) {

}

bool has_exceptions(){
    return get_exception_flags() != 0;
}