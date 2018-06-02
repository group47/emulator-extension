//
// Created by qs4617 on 02/06/18.
//

#include <assert.h>
#include "single_data_transfer.h"
#include "../../util/cpsr_util.h"
#include "../../util/operand_two_util.h"
#include "../../util/address.h"

#define IMMEDIATE_BIT_FLAG_SINGLE_DATE_TRANSFER 0

enum ExecutionExitCode execute_instruction_single_data_transfer(struct SingleDataTransferInstruction instruction) {
    if (!should_execute(instruction.cond)) {
        return DIDNT_EXECUTE;
    }

    // from ARM_doc, 4.9.4
    assert(instruction.Rn == PC && instruction.writeBackBit);
    assert(!instruction.immediateOffsetBit &&
           ((struct ShiftRegister*) &instruction.offset)->Rm != PC);


    uint32_t offset;

    if (!instruction.immediateOffsetBit) {
        offset = instruction.offset;
    } else {
        uint32_t dummy;
        offset = (uint32_t) get_operand2(instruction.offset,
                                         instruction.immediateOffsetBit,
                                         IMMEDIATE_BIT_FLAG_SINGLE_DATE_TRANSFER,
                                         &offset, &dummy);
    }

    // pre indexing
    uint32_t address = get_word_from_register(instruction.Rn);

    if (instruction.prePostBit) {
        if (instruction.upDownBit) {
            address += offset;
        } else {
            address -= offset;
        }
    }

    // todo: make sure that the load/store function handles the nasty case with the endianess
    // todo: there should be a state to indicate memory access out of bound
    if (instruction.loadStoreBit) {
        if (instruction.byteWordBit) {
            set_byte_in_register(instruction.Rd, get_byte_from_memory(address));
        } else {
            set_word_in_register(instruction.Rd, get_word_from_memory(address));
        }
    } else {
        // from ARM_doc, 4.9.4
        if (instruction.Rd == PC) {
            set_word_from_memory(address, get_current_instruction_address());
        } else {
            if (instruction.byteWordBit) {
                set_byte_from_memory(address, get_byte_from_register(address));
            } else {
                set_word_from_memory(address, get_word_from_register(address));
            }
        }
    }

    // I need a better solution for this duplication
    // post indexing
    if (!instruction.prePostBit) {
        // from ARM_doc, 4.9.1
        // W = 1 is redundant for post addressing index
        // according to documentation, you cannot have both W = 1 and P = 0
        assert(!instruction.writeBackBit);
        if (instruction.upDownBit) {
            set_word_in_register(instruction.Rn, address += offset);
        } else {
            set_word_in_register(instruction.Rn, address -= offset);
        }
    }

    if (instruction.writeBackBit) {
        set_word_in_register(instruction.Rn, address);
    }

    // todo: pass other execution exit code
    return OK;

}