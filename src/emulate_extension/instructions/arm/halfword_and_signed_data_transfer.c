//
// Created by fpn17 on 02/06/18.
//

#include <assert.h>
#include "halfword_and_signed_data_transfer.h"
#include "../../util/cpsr_util.h"


enum ExecutionExitCode execute_halfword_and_signed_data_transfer_register_offset(struct HalfWordAndSignedDataTransferRegisterOffset instruction){
    //todo dupe
    assert(!instruction.signed_ && !instruction.halfword);
    assert(instruction.shouldBe0 == 0b0);
    assert(instruction.shouldBe0b000 == 0b000);
    assert(instruction.shouldBe00001 == 0b00001);
    assert(instruction.shouldBe1 == 0b1);
    if(!should_execute(instruction.cond)){
        return DIDNT_EXECUTE;
    }
    const ByteAddress baseAddress = get_register(instruction.Rn);
    const ByteAddress offset = get_register(instruction.Rm);

    ByteAddress final_address = baseAddress;
    if(instruction.indexing == PRE){
        final_address = getFinalAddress(instruction.upDown, baseAddress, offset);
    }
    if(instruction.loadStore == LOAD){
        if(instruction.halfword) {
            if(instruction.signed_){
                set_register(instruction.Rd,get_half_word_from_memory_sign_extended(final_address));
            }else{
                set_register(instruction.Rd,get_half_word_from_memory(final_address));
            }
        }
        else{
            if(instruction.signed_){
                set_register(instruction.Rd,get_byte_from_memory_sign_extended(final_address));
            }else{
                set_register(instruction.Rd,get_byte_from_memory(final_address));
            }
        }
    }else if (instruction.loadStore == STORE){
        if(instruction.halfword) {
            if(instruction.signed_){
                set_half_word_from_memory_sign_extended(final_address,get_register(instruction.Rd));
            }else{
                set_half_word_from_memory(final_address,get_register(instruction.Rd));
            }
        }
        else{
            if(instruction.signed_){
                set_byte_from_memory_sign_extended(final_address,get_register(instruction.Rd));
            }else{
                assert(false);
            }
        }
    }else{
        assert(false);
    }

    if(instruction.indexing == POST){
        final_address = getFinalAddress(instruction.upDown, baseAddress, offset);
    }
    if(instruction.writeBack){
        set_register(instruction.Rn,final_address);
    }
    return OK;

}

const ByteAddress getFinalAddress(bool upDown, const ByteAddress baseAddress,
                const ByteAddress offset) {
    ByteAddress final_address;
    if (upDown) {
        final_address = baseAddress + offset;//offset is unsigned
    } else {
        final_address = baseAddress - offset;
    }
    return final_address;
}


enum ExecutionExitCode execute_halfword_and_signed_data_transfer_immediate_offset(struct HalfWordAndSignedDataTransferImmediateOffset instruction){
    //todo duplication
    assert(instruction.shouldBe0b000 == 0b000);
    assert(instruction.filler1position4 == 0b1);
    assert(instruction.filler1Position22 == 0b1);
    assert(instruction.filler1position7 == 0b1);
    if(!should_execute(instruction.cond)){
        return DIDNT_EXECUTE;
    }
    const ByteAddress baseAddress = get_register(instruction.Rn);
    const ByteAddress offset = get_offset(instruction);

    ByteAddress final_address = baseAddress;
    if(instruction.indexing == PRE){
        final_address = getFinalAddress(instruction.upDown, baseAddress, offset);
    }
    if(instruction.loadStore == LOAD){
        if(instruction.halfword) {
            if(instruction.signed_){
                set_register(instruction.Rd,get_half_word_from_memory_sign_extended(final_address));
            }else{
                set_register(instruction.Rd,get_half_word_from_memory(final_address));
            }
        }
        else{
            if(instruction.signed_){
                set_register(instruction.Rd,get_byte_from_memory_sign_extended(final_address));
            }else{
                set_register(instruction.Rd,get_byte_from_memory(final_address));
            }
        }
    }else if (instruction.loadStore == STORE){
        if(instruction.halfword) {
            if(instruction.signed_){
                set_half_word_from_memory_sign_extended(final_address,get_register(instruction.Rd));
            }else{
                set_half_word_from_memory(final_address,get_register(instruction.Rd));
            }
        }
        else{
            if(instruction.signed_){
                set_byte_from_memory_sign_extended(final_address,get_register(instruction.Rd));
            }else{
                assert(false);
            }
        }
    }else{
        assert(false);
    }

    if(instruction.indexing == POST){
        final_address = getFinalAddress(instruction.upDown, baseAddress, offset);
    }
    if(instruction.writeBack){
        set_register(instruction.Rn,final_address);
    }
    return OK;
}

const ByteAddress get_offset(struct HalfWordAndSignedDataTransferImmediateOffset instruction) {
    return instruction.offsetHighNibble << 4 + instruction.offsetLowNibble;
}