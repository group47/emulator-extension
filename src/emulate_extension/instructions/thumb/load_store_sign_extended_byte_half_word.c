//
// Created by fpn17 on 02/06/18.
//

#include <assert.h>
#include "load_store_sign_extended_byte_half_word.h"
#include "../../util/common_enums.h"
#include "../../state/memory.h"
#include "../../state/emulator_state.h"

enum ExecutionExitCode execute_load_store_sign_extended_byte_half_word(struct LoadStoreSignExtendedByteHalfword instruction){
    ByteAddress final_address = get_word_from_register(instruction.Rb) + get_word_from_register(instruction.Ro);
    if(!instruction.hFlag && !instruction.signed_){
        assert(final_address %2 == 0);
        set_half_word_from_memory(final_address/2,get_word_from_register(instruction.Rd));
    }
    if(instruction.hFlag && !instruction.signed_){
        assert(final_address %2 == 0);
        set_word_in_register(instruction.Rd,0);
        set_word_in_register(instruction.Rd,get_half_word_from_memory(final_address/2));
    }
    if(!instruction.hFlag && instruction.signed_){
        assert(final_address %2 == 0);
        set_word_in_register(instruction.Rd,0);
        set_word_in_register(instruction.Rd,get_byte_from_memory_sign_extended(final_address/2));
    }
    if(instruction.hFlag && instruction.signed_){
        assert(final_address %2 == 0);
        set_word_in_register(instruction.Rd,0);
        set_word_in_register(instruction.Rd,get_half_word_from_memory_sign_extended(final_address/2));
    }
    return OK;
}