//
// Created by qs4617 on 02/06/18.
//

#include <assert.h>
#include <x86intrin.h>
#include "single_data_transfer.h"
#include "../../util/cpsr_util.h"
#include "../../util/operand_two_util.h"
#include "../../util/address.h"

#define IMMEDIATE_BIT_FLAG_SINGLE_DATE_TRANSFER 0

// the abort is handled here
enum ExecutionExitCode execute_instruction_single_data_transfer(struct SingleDataTransferInstruction instruction) {
    if (!should_execute(instruction.cond)) {
        return DIDNT_EXECUTE;
    }

    // from ARM_doc 4.9.1, "write back bit is set to zero in the case of post-indexed addressing"
    //assert(!instruction.prePostBit || !instruction.writeBackBit);

    // from ARM_doc, 4.9.4, "write back bit is set to zero when r15 is Rn"
    assert(!instruction.Rn == PC_ADDRESS || !instruction.writeBackBit);

    // from ARM_doc 4.9.1, "r15 must not be specified as Rm"
    assert(instruction.immediateOffsetBit ||
           !((struct ImmediateFalseShiftByRegisterTrue*) &instruction.offset)->Rm == PC_ADDRESS);


    uint8_t oldBase = instruction.Rn;
    uint32_t offset;
    uint32_t address = get_word_from_register(instruction.Rn);

    if (!instruction.immediateOffsetBit) {
        offset = instruction.offset;
    } else {
        bool dummy;
        offset = (uint32_t) get_operand2(instruction.offset,
                                         instruction.immediateOffsetBit,
                                         IMMEDIATE_BIT_FLAG_SINGLE_DATE_TRANSFER,
                                         &offset, &dummy); //dummy bool
    }

    // pre indexing
    if (instruction.prePostBit) {
        if (instruction.upDownBit) {
            address += offset;
        } else {
            address -= offset;
        }
    }

    // todo: make sure that the load/store function handles the nasty case with the endianess
    // todo: there should be a state to indicate memory access out of bound
    if (instruction.loadStoreBit == LOAD) {
        if (instruction.byteWordBit) {
            set_byte_in_register(instruction.Rd, get_byte_from_memory(address));
        } else {
            // from ARM_doc, the doc indicates both rotate and clear higher level if the address is not word aligned
            // this implementation is based on rotate
            Word wordInMemory = get_word_from_memory(address);
            wordInMemory = __rord(wordInMemory, 8 * (address % 4));
            set_word_in_register(instruction.Rd, wordInMemory);
        }
    } else {
        // from ARM_doc, 4.9.4
        if (instruction.Rd == PC_ADDRESS) {
            assert(get_current_instruction_address() + 12 == get_word_from_register(instruction.Rd));
            set_word_from_memory(address, get_current_instruction_address() + 12);
        } else {
            if (instruction.byteWordBit) {
                set_byte_from_memory(address, get_byte_from_register(address));
            } else {
                set_word_from_memory(address, get_word_from_register(address));
            }
        }
    }

    // post indexing
    if (!instruction.prePostBit) {
        if (instruction.upDownBit) {
            set_word_in_register(instruction.Rn, address += offset);
        } else {
            set_word_in_register(instruction.Rn, address -= offset);
        }
    }

    if (instruction.writeBackBit) {
        set_word_in_register(instruction.Rn, address);
    }

    // if data abort happens, write back modified base registers
    if (has_exception_flag(DATA_ABORT)) {
        set_word_in_register(instruction.Rn, oldBase);
    }

    return OK;

}