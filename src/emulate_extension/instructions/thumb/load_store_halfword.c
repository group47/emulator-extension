//
// Created by fpn17 on 02/06/18.
//

#include <stdbool.h>
#include <assert.h>
#include "load_store_halfword.h"
#include "../../state/emulator_state.h"

enum ExecutionExitCode execute_load_store_halfword(struct LoadStoreHalfWord instruction){
    ByteAddress final_address = get_word_from_register(instruction.Rb) + (instruction.offset5 >> 1);
    if(instruction.loadStore == STORE){
        assert(final_address % 2 == 0);
        set_half_word_from_memory(final_address/2,get_word_from_register(instruction.Rd));
    }else if(instruction.loadStore == LOAD){
        assert(final_address %2 == 0);
        set_word_in_register(instruction.Rd,0);
        set_word_in_register(instruction.Rd,get_half_word_from_memory(final_address/2));
    }else{
        assert(false);
    }
    return OK;
}