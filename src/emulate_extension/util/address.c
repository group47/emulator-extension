//
// Created by qs4617 on 02/06/18.
//

#include <stdbool.h>
#include <assert.h>
#include "address.h"
#include "../state/emulator_state.h"

ByteAddress get_current_instruction_address() {
    //assert(false);
    //return 0;
    return (get_word_from_register(PC_ADDRESS) - 8) ;
}

