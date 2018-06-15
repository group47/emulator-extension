//
// Created by mhl1817 on 02/06/18.
//

#include "load_store_with_immediate_offset.h"
#include "../../state/emulator_state.h"

enum ExecutionExitCode execute_instruction_load_store_with_immeditate_offset(
        const struct LoadStoreWithImmediateOffsetInstruction instruction) {

    uint8_t offset = (uint8_t) (instruction.offset * 4);

    if (instruction.byteTransfer) {

        Byte result = get_byte_from_register(instruction.Rb) + offset;

        if (instruction.loadMemory) {
            set_byte_in_register(instruction.Rd, result);
        } else {
            set_byte_in_memory(result, get_byte_from_register(instruction.Rd));
        }

    } else {

        ByteAddress result = get_word_from_register(instruction.Rb) + offset;

        if (instruction.loadMemory) {
            set_word_in_register(instruction.Rd, result);
        } else {
            set_word_in_memory(result, get_word_from_register(instruction.Rd));
        }
    }

    return OK;
}
