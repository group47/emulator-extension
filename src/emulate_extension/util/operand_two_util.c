//
// Created by francis on 6/2/18.
//

#include <stdint.h>
#include <stdbool.h>
#include <x86intrin.h>
#include <assert.h>
#include "operand_two_util.h"
#include "../state/emulator_state.h"


int get_operand2(uint16_t secondOperand,
                 bool immediate,
                 bool flag,
                 uint32_t *operand2_val,
                 bool *carry_out) {
    //todo this needs change in main emulator.
    if (immediate == flag) {

        struct ImmediateTrue immediateTrue = *(struct ImmediateTrue *) &secondOperand;
        //rotate stack overflow community wiki:
        //https://stackoverflow.com/questions/776508/best-practices-for-circular-shift-rotate-operations-in-c
        uint32_t imm = immediateTrue.Imm;
        *operand2_val = __rord(imm, 2 * immediateTrue.rotate);
    } else {
        //get immediate false's field
        struct ImmediateFalseShiftByRegisterFalse
                immediateFalse = *(struct ImmediateFalseShiftByRegisterFalse *) &secondOperand;
        uint32_t shift_amount;
        enum ShiftType shift_type;
        if (immediateFalse.shift_by_register) {

            struct ImmediateFalseShiftByRegisterTrue
                    shiftByRegister = *(struct ImmediateFalseShiftByRegisterTrue *) &secondOperand;

            assert(flag != IMMEDIATE_BIT_FLAG_SINGLE_DATE_TRANSFER);
            assert(shiftByRegister.filler0 == 0b0);
            assert(shiftByRegister.Rs != PC_ADDRESS);

            shift_amount = (uint8_t) (get_word_from_register(shiftByRegister.Rs) &
                                      0xff); //last byte//todo is this correct
            shift_type = shiftByRegister.shift_type;
            *operand2_val = get_word_from_register(shiftByRegister.Rm);
        } else {

            assert(flag != IMMEDIATE_BIT_FLAG_SINGLE_DATE_TRANSFER || immediateFalse.Rm != PC_ADDRESS);

            shift_amount = immediateFalse.shift_amount;
            shift_type = immediateFalse.shift_type;
            *operand2_val = get_word_from_register(immediateFalse.Rm);
        }

        //compute immediate false's value
        if (shift_amount == 0) {
            *carry_out = getCPSR().C;
            if (shift_type == ror && !immediateFalse.shift_by_register) {
                *operand2_val >>= 1;
                if (getCPSR().C) {
                    *operand2_val |= (0x1 << 31);
                }
            }
            if(shift_type == lsr){
                //this means lsr #32
                *carry_out = (*operand2_val & 0xf0000000) ? true: false;
                *operand2_val = 0;
            }
        } else {
            switch (shift_type) {
                case lsl:
                    operand_two_lsl(operand2_val, carry_out, shift_amount, immediateFalse.shift_by_register);
                    break;
                case lsr:
                    operand_two_lsr(operand2_val, carry_out, shift_amount, immediateFalse.shift_by_register);
                    break;
                case asr:
                    operand_two_asr(operand2_val, carry_out, shift_amount, immediateFalse.shift_by_register);
                    break;
                case ror:
                    operand_two_ror(operand2_val, carry_out, shift_amount, immediateFalse.shift_by_register);
                    break;
                default:
                    assert(false);
            }
        }
    }
    return OK;

}

void operand_two_ror(uint32_t *operand2_val, bool *carry_out, uint32_t shift_amount, bool shiftByRegister) {
    shift_amount %= 32;
    if (shift_amount == 0 && shiftByRegister) {
        *carry_out = ((*operand2_val >> 31) & 0x1) != 0;
    } else {
        *operand2_val = __rord(*operand2_val, shift_amount - 1);
        *carry_out = (*operand2_val & 0x1) != 0;
        *operand2_val = __rord(*operand2_val, 1);
    }
}

void operand_two_asr(uint32_t *operand2_val, bool *carry_out, uint32_t shift_amount, bool shiftByRegister) {
    if (shift_amount == 0 && shiftByRegister) {
        return;
    }
    uint32_t ar_bit = *operand2_val & (0b1 << 31);
    if (shift_amount < 32 || !shiftByRegister) {
        for (int i = 0; i < shift_amount - 1; ++i) {
            *operand2_val = (*operand2_val >> 1) | ar_bit;
        }
        *carry_out = (*operand2_val & 0x1) != 0;
        *operand2_val = (*operand2_val >> 1) | ar_bit;
    } else {
        *carry_out = ((ar_bit >> 31) & 0x1) != 0;
        *operand2_val = ar_bit ? 0xffffffff : 0x0;
    }
}

void operand_two_lsr(uint32_t *operand2_val, bool *carry_out, uint32_t shift_amount, bool shiftByRegister) {
    if (shift_amount == 0) {
        return;
    }
    if (shift_amount < 32 || !shiftByRegister) {
        *operand2_val >>= shift_amount - 1;
        *carry_out = (*operand2_val & 0x1) != 0;
        *operand2_val >>= 1;
    } else {
        *carry_out = (shift_amount > 32) ? false : (((*operand2_val >> 31) & 0x1) != 0);
        *operand2_val = 0;
    }
}

void operand_two_lsl(uint32_t *operand2_val, bool *carry_out, uint32_t shift_amount, bool shiftByRegister) {
    if (shift_amount == 0) {
        return;
    }
    if (shift_amount < 32 || !shiftByRegister) {
        *operand2_val <<= shift_amount - 1;
        *carry_out = (*operand2_val >> 31) != 0;
        *operand2_val <<= 1;
    } else {
        *carry_out = (shift_amount > 32) ? false : ((*operand2_val & 0x1) != 0);
        *operand2_val = 0;
    }
}
