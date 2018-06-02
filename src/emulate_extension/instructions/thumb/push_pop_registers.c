//
// Created by qs4617 on 02/06/18.
//

#include "push_pop_registers.h"
#include "../../state/emulator_state.h"

enum ExecutionExitCode execute_instruction_push_pop_registers(struct PushPopRegistersInstruction instruction) {

    for (int i = 0; i < NUM_GENERAL_PURPOSE_REGISTERS_THUMB; i++) {

        if (instruction.registerList & 0x1 << i) {
            if (instruction.loadStoreBit == STORE) {
                set_word_from_memory(get_word_from_register(STACK_POINTER_ADDRESS),
                                     get_word_from_register(i));
                set_word_in_register(STACK_POINTER_ADDRESS,
                                     get_word_from_register(STACK_POINTER_ADDRESS) - 4);

            }
        } else {
            set_word_in_register(i,
                                 get_word_from_memory(get_word_from_register(STACK_POINTER_ADDRESS) + 4));
            set_word_in_register(STACK_POINTER_ADDRESS,
                                 get_word_from_register(STACK_POINTER_ADDRESS) + 4);
        }
    }

    if (instruction.PCLRBit) {
        if (instruction.loadStoreBit == STORE) {
            set_word_from_memory(get_word_from_register(STACK_POINTER_ADDRESS),
                                     get_word_from_register(LR_ADDRESS));
                set_word_in_register(STACK_POINTER_ADDRESS,
                                     get_word_from_register(STACK_POINTER_ADDRESS) - 4);

        } else {
            set_word_in_register(PC_ADDRESS,
                                 get_word_from_memory(get_word_from_register(STACK_POINTER_ADDRESS) + 4));
            set_word_in_register(STACK_POINTER_ADDRESS,
                                 get_word_from_register(STACK_POINTER_ADDRESS) + 4);
        }
    }
    return OK;
}
