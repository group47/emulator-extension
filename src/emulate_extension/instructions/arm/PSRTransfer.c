//
// Created by qs4617 on 03/06/18.
//
#include "stdio.h"
#include "PSRTransfer.h"
#include "../../util/cpsr_util.h"
#include "../../util/operand_two_util.h"

enum ExecutionExitCode
execute_instruction_transfer_psr_contents_to_register(struct TransferPSRContentsToRegister instruction) {
    if (!should_execute(instruction.cond)) {
        return DIDNT_EXECUTE;
    }

    if (instruction.sourcePSR) {
        struct CPSR_Struct spsr_by_mode = get_SPSR_by_mode();
        set_word_in_register(instruction.Rd, *((uint32_t*)&spsr_by_mode));
    } else {
        struct CPSR_Struct cpsr = getCPSR();
        set_word_in_register(instruction.Rd, *((uint32_t*)&cpsr));
    }
    return OK;
}

enum ExecutionExitCode
execute_instruction_transfer_register_contents_to_psr(struct TransferRegisterContentsToPSR instruction) {
    if (!should_execute(instruction.cond)) {
        return DIDNT_EXECUTE;
    }

    Word registerVal =get_word_from_register(instruction.Rm);
    if (instruction.destinationPSR) {
        setSPSR(*((struct CPSR_Struct*) &registerVal));
    } else {
        setCPSR(*(struct CPSR_Struct*) &registerVal);
    }
    return OK;
}

enum ExecutionExitCode
execute_instruction_transfer_register_contents_or_immediate_value_to_psrflag(
        struct TransferRegisterContentsOrImmediateValueToPSRFlag instruction) {
    if (!should_execute(instruction.cond)) {
        return DIDNT_EXECUTE;
    }

    Word val = 0;
    get_operand2(instruction.sourceOperand, instruction.immediateOperand, 1, &val, false); //does dummy bool works?

    if (instruction.destinationPSR) {
        setSPSR(*(struct CPSR_Struct*) &val);
    } else {
        setCPSR(*(struct CPSR_Struct*) &val);
    }

    return OK;
}

