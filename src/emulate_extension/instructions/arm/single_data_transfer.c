//
// Created by qs4617 on 02/06/18.
//

#include <assert.h>
#include <x86intrin.h>
#include "single_data_transfer.h"
#include "../../util/cpsr_util.h"
#include "../../util/operand_two_util.h"
#include "../../util/address.h"


// the abort is handled here
enum ExecutionExitCode execute_instruction_single_data_transfer(struct SingleDataTransferInstruction instruction) {
    if (!should_execute(instruction.cond)) {
        return DIDNT_EXECUTE;
    }

    // from ARM_doc 4.9.1, "write back bit is set to zero in the case of post-indexed addressing"
    //assert(!instruction.prePostBit || !instruction.writeBackBit);

    // from ARM_doc, 4.9.4, "write back bit is set to zero when r15 is Rn"
    assert(instruction.Rn != PC_ADDRESS || !instruction.writeBackBit);
    assert(instruction.prePostBit || !instruction.writeBackBit); //arm-doc 4-29

    // from ARM_doc 4.9.1, "r15 must not be specified as Rm"
    //assert(instruction.immediateOffsetBit ||
      //     !((struct ImmediateFalseShiftByRegisterTrue*) &(uint8_t)instruction.offset)->Rm == PC_ADDRESS);

    Word oldBase = get_word_from_register(instruction.Rn);
    /*
    uint32_t offset;
    ByteAddress address = get_word_from_register(instruction.Rn);
    if (instruction.Rn == PC_ADDRESS) {
        address -= 8;
    }

    if (!instruction.immediateOffsetBit) {
        offset = instruction.offset;
    } else {
        bool dummy;
        get_operand2(instruction.offset, instruction.immediateOffsetBit, IMMEDIATE_BIT_FLAG_SINGLE_DATE_TRANSFER, &offset, &dummy); //dummy bool
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
    Word val;
    if (instruction.loadStoreBit == LOAD) {
        if (instruction.byteWordBit) {
            val = (Word) get_byte_from_memory(address) & 0xff;
        } else {
            // from ARM_doc, the doc indicates both rotate and clear higher level if the address is not word aligned
            // this implementation is based on rotate
            val = get_word_from_memory(address);
            val = __rord(val, 8 * (address % 4));
        }
        set_word_in_register(instruction.Rd, val);
    } else {
        // from ARM_doc, 4.9.4
        if (instruction.Rd == PC_ADDRESS) {
//            assert(get_current_instruction_address() + 12 == get_word_from_register(instruction.Rd));
            set_word_in_memory(address, get_current_instruction_address() + 12);
        } else {
            val = get_word_from_register(instruction.Rd);
            if (instruction.byteWordBit) {
                val = (val & 0xff) * 0x01010101; //copy last byte across
            } else {
                val = __rord(val, 8 * (val % 4));
            }
            set_word_in_memory(address, val);
        }
    }

    // post indexing
    if (!instruction.prePostBit) {
        if (instruction.upDownBit) {
            address += offset;
        } else {
            address -= offset;
        }
        set_word_in_register(instruction.Rn, address);
    }

    if (instruction.writeBackBit) {
        set_word_in_register(instruction.Rn, address);
    }*/

    //calculating offset
    uint32_t offset;
    if (!instruction.immediateOffsetBit) {
        offset = instruction.offset;
    } else {
        bool dummy;
        get_operand2(instruction.offset, instruction.immediateOffsetBit, IMMEDIATE_BIT_FLAG_SINGLE_DATE_TRANSFER, &offset, &dummy); //dummy bool
    }

    ByteAddress rn_val = get_word_from_register(instruction.Rn);
    ByteAddress rd_val = get_word_from_register(instruction.Rd);

    // pre indexing
    if (instruction.prePostBit) {
        if (instruction.upDownBit) {
            rn_val += offset;
        } else {
            rn_val -= offset;
        }
    }

    if (instruction.loadStoreBit) {
        Word word;
        if (instruction.byteWordBit) {
            word = (Word) get_byte_from_memory(rn_val) & 0xff;
        } else {
            word = get_word_from_memory(rn_val);
            word = __rord(word, 8 * (rn_val % 4));
        }
        set_word_in_register(instruction.Rd, word);
    } else {
        if (instruction.Rd == PC_ADDRESS) {
            set_word_in_memory(rn_val, get_current_instruction_address() + 12);
        } else {
            if (instruction.byteWordBit) {
                //word = (rd_val & 0xff) * 0x01010101; //copy last byte across
                set_byte_in_memory(rn_val, (Byte) (rd_val & 0xff));
            } else {
                //word = __rord(rd_val, 8 * (rd_val % 4));
                set_word_in_memory(rn_val, rd_val);
            }
        }
    }

    // post indexing
    if (!instruction.prePostBit) {
        if (instruction.upDownBit) {
            rn_val += offset;
        } else {
            rn_val -= offset;
        }
        set_word_in_register(instruction.Rn, rn_val);
    }

    if (instruction.writeBackBit) {
        set_word_in_register(instruction.Rn, rn_val);
    }


    // if data abort happens, write back modified base registers
    if (has_exception_flag(DATA_ABORT)) {
        set_word_in_register(instruction.Rn, oldBase);
    }

    return OK;

}