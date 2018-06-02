//
// Created by fpn17 on 02/06/18.
//

#include "move_shifted_register.h"
#include "../../util/common_enums.h"
#include "../../state/emulator_state.h"
#include "../../util/shift_util.h"


enum ExecutionExitCode execute_move_shifted_register(struct MoveShiftedRegister instruction){
    switch(instruction.Op){
        case THUMB_SHIFTED_REGISTER_LSL:
            set_word_in_register(instruction.Rd,get_word_from_register(instruction.Rs) << instruction.offset5);
            break;
        case THUMB_SHIFTED_REGISTER_LSR:
            set_word_in_register(instruction.Rd,get_word_from_register(instruction.Rs) >> instruction.offset5);
            break;
        case THUMB_SHIFTED_REGISTER_ASR:
            set_word_in_register(instruction.Rd,arithmeticRightShift(get_word_from_register(instruction.Rs),instruction.offset5));//todo vheck casting occurs correctly
            break;
    }
    return OK;
}