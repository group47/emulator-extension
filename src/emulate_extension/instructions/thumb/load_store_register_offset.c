//
// Created by fpn17 on 02/06/18.
//

#include <assert.h>
#include "load_store_register_offset.h"
#include "../../state/memory.h"
#include "../../state/emulator_state.h"

enum ExecutionExitCode execute_instruction_load_store_register_offset(struct LoadStoreRegisterOffset instruction) {
    ByteAddress final_address =
            get_word_from_register(instruction.Ro) + get_word_from_register(instruction.Rb);//todo is this signed
    if (instruction.loadStore == LOAD) {
        if (instruction.load_byte) {
            set_byte_in_register(instruction.Rd, get_byte_from_memory(final_address));
        } else {
            assert(final_address % 4 == 0);
            set_word_in_register(instruction.Rd, get_word_from_memory(final_address));
        }
    } else if (instruction.loadStore == STORE) {
        if (instruction.load_byte) {
            set_byte_in_memory(final_address, instruction.Rd);
        } else {
            assert(final_address % 4 == 0);
            set_word_in_memory(final_address, instruction.Rd);
        }
    } else {
        assert(false);
    }
    return OK;
}