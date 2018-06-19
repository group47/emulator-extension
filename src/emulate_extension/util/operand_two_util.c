//
// Created by francis on 6/2/18.
//

#include <stdint.h>
#include <stdbool.h>
#include <x86intrin.h>
#include <assert.h>
#include "operand_two_util.h"
#include "../state/emulator_state.h"

bool shift_by_immediate_amount_0(bool shift_by_register, uint32_t shift_amount) {
    return shift_amount == 0 && !shift_by_register;
}

bool shift_by_register_32_or_more(bool shift_by_register, uint32_t shift_amount) {
    return shift_amount >= 32 && shift_by_register;
}

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
                                      0xff); //last byte
            shift_type = shiftByRegister.shift_type;
            *operand2_val = get_word_from_register(shiftByRegister.Rm);
            if(shiftByRegister.Rm == PC_ADDRESS){// If pc is used the pc is one byte further ahead.
                *operand2_val += 4;
            }
        } else {

            assert(flag != IMMEDIATE_BIT_FLAG_SINGLE_DATE_TRANSFER || immediateFalse.Rm != PC_ADDRESS);

            shift_amount = immediateFalse.shift_amount;
            shift_type = immediateFalse.shift_type;
            *operand2_val = get_word_from_register(immediateFalse.Rm);
        }

        bool shift_by_register = immediateFalse.shift_by_register;
        if (shift_amount == 0 && shift_by_register) {
            *carry_out = getCPSR().C;
        } else {
            switch (shift_type) {
                case lsl: operand_two_lsl(operand2_val, carry_out, shift_amount, shift_by_register); break;
                case lsr: operand_two_lsr(operand2_val, carry_out, shift_amount, shift_by_register); break;
                case asr: operand_two_asr(operand2_val, carry_out, shift_amount, shift_by_register); break;
                case ror: operand_two_ror(operand2_val, carry_out, shift_amount, shift_by_register); break;
                default: assert(false);
            }
        }
    }
    return OK;
}

void operand_two_ror(uint32_t *operand2_val, bool *carry_out, uint32_t shift_amount, bool shift_by_register) {
    if (shift_by_immediate_amount_0(shift_by_register, shift_amount)) {
        *carry_out = (*operand2_val & 0x1) != 0;
        *operand2_val >>= 1;
        if (getCPSR().C) {
            *operand2_val |= (0x1 << 31);
        }
    } else if (shift_by_register && shift_amount == 32) {
        *carry_out = (*operand2_val & (0x1 << 31)) != 0;
    } else {
        shift_amount %= 32;
        assert(shift_amount < 32);
        *operand2_val = __rord(*operand2_val, shift_amount - 1);
        *carry_out = (*operand2_val & 0x1) != 0;
        *operand2_val = __rord(*operand2_val, 1);
    }
}

void operand_two_asr(uint32_t *operand2_val, bool *carry_out, uint32_t shift_amount, bool shift_by_register) {
    const uint32_t bit_31 = *operand2_val & (0x1 << 31);
    if (shift_by_immediate_amount_0(shift_by_register, shift_amount)
        || shift_by_register_32_or_more(shift_by_register, shift_amount)) {
        *carry_out = bit_31 != 0;
        *operand2_val = (*carry_out) ? 0xffffffff : 0x0;
    } else {
        assert(shift_amount < 32);
        for (int i = 0; i < shift_amount - 1; ++i) {
            *operand2_val = (*operand2_val >> 1) | bit_31;
        }
        *carry_out = (*operand2_val & 0x1) != 0;
        *operand2_val = (*operand2_val >> 1) | bit_31;
    }
}

void operand_two_lsr(uint32_t *operand2_val, bool *carry_out, uint32_t shift_amount, bool shift_by_register) {
    if (shift_by_immediate_amount_0(shift_by_register, shift_amount)
        || shift_by_register_32_or_more(shift_by_register, shift_amount)) {
        *carry_out = (shift_amount <= 32) && ((*operand2_val & (0x1 << 31)) != 0);
        *operand2_val = 0;
    } else {
        assert(shift_amount < 32);
        *operand2_val >>= shift_amount - 1;
        *carry_out = (*operand2_val & 0x1) != 0;
        *operand2_val >>= 1;
    }
}

void operand_two_lsl(uint32_t *operand2_val, bool *carry_out, uint32_t shift_amount, bool shift_by_register) {
    if (shift_amount == 0) {
        *carry_out = getCPSR().C;
    } else if (shift_by_register_32_or_more(shift_by_register, shift_amount)) {
        *carry_out = (shift_amount <= 32) && ((*operand2_val & 0x1) != 0);
        *operand2_val = 0;
    } else {
        assert(shift_amount < 32);
        *operand2_val <<= shift_amount - 1;
        *carry_out = (*operand2_val & (0x1 << 31)) != 0;
        *operand2_val <<= 1;
    }
}
