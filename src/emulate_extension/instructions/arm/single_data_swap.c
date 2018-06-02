//
// Created by francis on 6/1/18.
//

#include <assert.h>
#include "single_data_swap.h"
#include "../../util/cpsr_util.h"


enum ExecutionExitCode execute_instruction_single_data_swap(struct SingleDataSwapInstruction instruction) {
    if (!should_execute(instruction.cond)) {
        return DIDNT_EXECUTE;
    }

    assert(instruction.Rd != PC_ADDRESS && instruction.Rn != PC_ADDRESS);

    if (instruction.byteWordBit) {
        ByteAddress swapAddress = get_word_from_register(instruction.Rn);
        Byte baseVal = get_byte_from_memory(swapAddress);
        set_byte_from_memory(swapAddress, get_byte_from_register(instruction.Rm));
        set_byte_in_register(instruction.Rd, baseVal);
    } else {
        WordAddress swapAddress = get_word_from_register(instruction.Rn);
        Word baseVal = get_word_from_memory(swapAddress);
        set_word_from_memory(swapAddress, get_word_from_register(instruction.Rm));
        set_word_in_register(instruction.Rd, baseVal);
    }

    return OK;
}
