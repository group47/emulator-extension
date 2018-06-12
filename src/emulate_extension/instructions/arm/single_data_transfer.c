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
    assert(instruction.prePostBit || !instruction.writeBackBit);

    // from ARM_doc, 4.9.4, "write back bit is set to zero when r15 is Rn"
    assert(instruction.Rn != PC_ADDRESS || !instruction.writeBackBit);

    ByteAddress rd_val = get_word_from_register(instruction.Rd);
    ByteAddress rn_val = get_word_from_register(instruction.Rn);
    const ByteAddress fixed_rn_val_clone = rn_val;

    //calculating offset
    uint32_t offset;
    if (!instruction.immediateOffsetBit) {
        offset = instruction.offset;
    } else {
        bool dummy;
        get_operand2(instruction.offset, instruction.immediateOffsetBit, IMMEDIATE_BIT_FLAG_SINGLE_DATE_TRANSFER,
                     &offset, &dummy);
    }

    // pre indexing
    if (instruction.prePostBit) {
        if (instruction.upDownBit) {
            rn_val += offset;
        } else {
            rn_val -= offset;
        }
    }

    //rn_val -= 0x10000;

    //load-store
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
    }

    if (!instruction.prePostBit || instruction.writeBackBit) {
        set_word_in_register(instruction.Rn, rn_val);
    }

    // if data abort happens, write back modified base registers
    if (has_exception_flag(DATA_ABORT)) {
        //todo this won't work, because registers will no longer allow writing.
        set_word_in_register(instruction.Rn, fixed_rn_val_clone);
    }

    return OK;

}