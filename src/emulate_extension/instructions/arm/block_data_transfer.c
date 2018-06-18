//
// Created by qs4617 on 02/06/18.
//

#include <assert.h>
#include "block_data_transfer.h"
#include "../../util/cpsr_util.h"
#include "../../util/address.h"


enum ExecutionExitCode execute_instruction_block_data_transfer(struct BlockDataTransferInstruction instruction) {
    if (!should_execute(instruction.cond)) {
        return DIDNT_EXECUTE;
    }

    assert(instruction.registerList != 0);
    assert(instruction.Rn != PC_ADDRESS);
    if (instruction.psrAndForceUserBit)
        assert(get_operating_mode() != usr); // from ARM_doc, 4.11.4

    const ByteAddress rn_val = get_word_from_register(instruction.Rn);
    ByteAddress address = rn_val;

    uint32_t numOfRegisterUsed = 0;

    for (int i = 0; i < NUM_GENERAL_PURPOSE_REGISTERS_ARM; i++) {
        if (instruction.registerList & 0x1 << i) {
            numOfRegisterUsed++;
        }
    }

    // if access illegal, set the data abort flag
    get_word_from_memory(address + 4 * (numOfRegisterUsed - 1));

    uint16_t maskPC = 0x1 << 15;
    uint32_t offset = numOfRegisterUsed * 4;

    bool R15InRegisterList = instruction.registerList & maskPC;
    enum OperatingMode oldMode = get_operating_mode();
    bool userBankTransfer = (!instruction.loadStoreBit
                             && instruction.psrAndForceUserBit
                             && R15InRegisterList) ||
                            (!R15InRegisterList && instruction.psrAndForceUserBit);

    if (instruction.prePostIndexingBit) {
        if (instruction.upDownBit) {
            address += offset;
        } else {
            address -= offset;
        }
    }

    if (userBankTransfer) {
        set_operating_mode(usr);
    }

    // todo: check if the transfer of banking of register actually fit the specication for this instruction


    uint8_t registers_used = 0;
    for (uint8_t i = 0; i < NUM_REGISTER_IN_REGISTER_LIST; i++) {
        if (instruction.registerList & (0x1 << i)) {

            R15InRegisterList = i == PC_ADDRESS ? true : R15InRegisterList;

            if (instruction.loadStoreBit) {
                set_word_in_register(i, get_word_from_memory(address + (ByteAddress) registers_used * 4));
                if (instruction.psrAndForceUserBit && i == PC_ADDRESS) {
                    setCPSR(get_SPSR_by_mode());
                }
            } else {
                if (i == PC_ADDRESS) {
                    set_word_in_memory((ByteAddress) registers_used * 4 + address,
                                       get_current_instruction_address() + 12);
                } else {
                    set_word_in_memory((ByteAddress) registers_used * 4 + address, get_word_from_register(i));
                }
            }

            // Handle aborts
            if (has_exception_flag(DATA_ABORT) || has_exception_flag(PREFETCH_ABORT)) {
                if (instruction.loadStoreBit) {
                    if (instruction.writeBackBit) {
                        set_word_in_register(instruction.Rn, address);
                    }
                    break;
                }
            }
            registers_used++;
        }
    }

    if (instruction.writeBackBit) {
        if (instruction.upDownBit) {
            set_word_in_register(instruction.Rn, rn_val + (numOfRegisterUsed)* 4);
        } else {
            set_word_in_register(instruction.Rn, rn_val - (numOfRegisterUsed)* 4);
        }
    }

    set_operating_mode(oldMode);

    return OK;
}