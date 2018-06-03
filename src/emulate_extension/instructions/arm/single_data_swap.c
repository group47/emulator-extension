//
// Created by francis on 6/1/18.
//

#include <assert.h>
#include "../../util/cpsr_util.h"
#include "single_data_swap.h"


enum ExecutionExitCode execute_instruction_single_data_swap(struct SingleDataSwapInstruction instruction) {
    if (!should_execute(instruction.cond)) {
        return DIDNT_EXECUTE;
    }

    assert(instruction.Rd != PC_ADDRESS && instruction.Rn != PC_ADDRESS);

    Address swapAddress = get_word_from_register(instruction.Rn);
    Word oldRegisterVal = get_word_from_register(instruction.Rm);
    Word oldMemoryVal = get_word_from_memory(swapAddress);
    RegisterAddress oldRegister = instruction.Rd;

    if (instruction.byteWordBit) {
        Byte baseVal = get_byte_from_memory(swapAddress);
        set_byte_from_memory(swapAddress, get_byte_from_register(instruction.Rm));
        set_byte_in_register(instruction.Rd, baseVal);
    } else {
        Word baseVal = get_word_from_memory(swapAddress);
        set_word_from_memory(swapAddress, get_word_from_register(instruction.Rm));
        set_word_in_register(instruction.Rd, baseVal);
    }

    // if data abort happens, undo the swap
    if (has_exception_flag(DATA_ABORT)) {
        set_word_from_memory(swapAddress, oldMemoryVal);
        set_word_in_register(oldRegister, oldRegisterVal);
    }

    return OK;
}
