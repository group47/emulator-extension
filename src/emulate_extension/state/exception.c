//
// Created by qs4617 on 03/06/18.
//

#include <assert.h>
#include "exception.h"

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


}


/**
 *
 * exception vectors:
 * Address Exception Mode on entry
0x00000000 Reset Supervisor
0x00000004 Undefined instruction Undefined
0x00000008 Software interrupt Supervisor
0x0000000C Abort (prefetch) Abort
0x00000010 Abort (data) Abort
0x00000014 Reserved Reserved
0x00000018 IRQ IRQ
0x0000001C FIQ FIQ
 */

/**
 * from spec table 3-2:
 * BL MOV PC, R14 PC + 4 PC + 2
 * Where PC is the address of the BL/SWI/Undefined Instruction fetch which had
the prefetch abort.
 * @param oldcpsr
 */
void handle_branch(struct CPSR_Struct oldcpsr) {


}

/**
 * MOVS PC, R14_svc PC + 4 PC + 2
 * @param oldcpsr
 */
void handle_software_interrupt(struct CPSR_Struct oldcpsr) {
    //preserve address in link register
    if (get_mode() == ARM) {
        set_word_in_register(LR_ADDRESS, get_word_from_register(PC_ADDRESS) - 8 + 4);
    } else if (get_mode() == THUMB) {
        set_word_in_register(LR_ADDRESS, get_word_from_register(PC_ADDRESS) - 4 + 2);
    } else {
        assert(false);
    }
    //copy cpsr into spsr
    set_spsr_by_mode(getCPSR(), svc);
    //change mode
    set_operating_mode(svc);
    //set pc
    const ByteAddress swi_exception_vector = 0x00000008;
    set_word_in_register(PC_ADDRESS, swi_exception_vector);
    invalidate_pipeline();
}

void handle_undefined(struct CPSR_Struct oldcpsr) {
    //preserve address in link register
    if (get_mode() == ARM) {
        set_word_in_register(LR_ADDRESS, get_word_from_register(PC_ADDRESS) - 8 + 4);
    } else if (get_mode() == THUMB) {
        set_word_in_register(LR_ADDRESS, get_word_from_register(PC_ADDRESS) - 4 + 2);
    } else {
        assert(false);
    }
    //copy cpsr into spsr
    set_spsr_by_mode(oldcpsr, und);
    //change mode
    set_operating_mode(und);
    //set pc
    const ByteAddress undefined_exception_vector = 0x00000004;
    set_word_in_register(PC_ADDRESS, undefined_exception_vector);
    invalidate_pipeline();
}

/**
 * PABT SUBS PC, R14_abt, #4 PC + 4 PC + 4
 * here PC is the address of the BL/SWI/Undefined Instruction fetch which had
the prefetch abort.
 * @param oldcpsr
 */
void handle_prefetch_abort(struct CPSR_Struct oldcpsr) {
    //preserve address in link register
    if (get_mode() == ARM) {
        set_word_in_register(LR_ADDRESS, get_word_from_register(PC_ADDRESS) - 8 + 4);
    } else if (get_mode() == THUMB) {
        set_word_in_register(LR_ADDRESS, get_word_from_register(PC_ADDRESS) - 4 + 4);
    } else {
        assert(false);
    }
    //copy cpsr into spsr
    set_spsr_by_mode(oldcpsr, abt);
    //change mode
    set_operating_mode(abt);
    //set pc
    const ByteAddress prefetch_abort_vector = 0x0000000C;
    set_word_in_register(PC_ADDRESS, prefetch_abort_vector);
}

void handle_irq(struct CPSR_Struct oldcpsr) {
    assert(oldcpsr.I == false);
    //preserve address in link register
    if (get_mode() == ARM) {
        set_word_in_register(LR_ADDRESS, get_word_from_register(PC_ADDRESS) - 8 + 4);
    } else if (get_mode() == THUMB) {
        set_word_in_register(LR_ADDRESS, get_word_from_register(PC_ADDRESS) - 4 + 4);
    } else {
        assert(false);
    }
    //copy cpsr into spsr
    set_spsr_by_mode(oldcpsr, irq);
    //change mode
    set_operating_mode(irq);
    //set pc
    const ByteAddress irq_exception_vector = 0x0000001C;
    set_word_in_register(PC_ADDRESS, irq_exception_vector);
}

void handle_fiq(struct CPSR_Struct oldcpsr) {
    assert(oldcpsr.F == false);
    //preserve address in link register
    if (get_mode() == ARM) {
        set_word_in_register(LR_ADDRESS, get_word_from_register(PC_ADDRESS) - 8 + 4);
    } else if (get_mode() == THUMB) {
        set_word_in_register(LR_ADDRESS, get_word_from_register(PC_ADDRESS) - 4 + 4);
    } else {
        assert(false);
    }
    //copy cpsr into spsr
    set_spsr_by_mode(oldcpsr, fiq);
    //change mode
    set_operating_mode(fiq);
    //set pc
    const ByteAddress fiq_exception_vector = 0x00000018;
    set_word_in_register(PC_ADDRESS, fiq_exception_vector);
}

void handle_data_abort(struct CPSR_Struct oldcpsr) {
    assert(oldcpsr.F == false);
    //preserve address in link register
    if (get_mode() == ARM) {
        set_word_in_register(LR_ADDRESS, get_word_from_register(PC_ADDRESS) - 8 + 8);
    } else if (get_mode() == THUMB) {
        set_word_in_register(LR_ADDRESS, get_word_from_register(PC_ADDRESS) - 4 + 8);
    } else {
        assert(false);
    }
    //copy cpsr into spsr
    set_spsr_by_mode(oldcpsr, abt);
    //change mode
    set_operating_mode(abt);
    //set pc
    const ByteAddress data_abort_exception_vector = 0x00000010;
    set_word_in_register(PC_ADDRESS, data_abort_exception_vector);
}

bool has_exceptions() {
    return get_exception_flags() != 0;
}

bool has_exceptions_prev(struct CPUState *state_in) {
    return get_exception_flags_prev(state_in) != 0;
}