//
// Created by francis on 6/2/18.
//

#ifndef SRC_OPERAND_TWO_UTIL_H
#define SRC_OPERAND_TWO_UTIL_H

#include "../basic_typedefs.h"


enum ShiftType {
  lsl = 0b00,
  lsr = 0b01,
  asr = 0b10,
  ror = 0b11
};


struct ImmediateTrue{
    uint8_t Imm: 8;
    uint8_t rotate: 4;
}__attribute__((packed));


struct ImmediateFalseShiftByRegisterTrue{
    RegisterAddress Rm : 4;
    bool shift_by_register: 1;//should be true
    enum ShiftType shift_type: 2;
    bool filler0:1; //should be  0
    RegisterAddress Rs:4;
}__attribute__((packed));


struct ImmediateFalseShiftByRegisterFalse{
    RegisterAddress Rm : 4;
    bool shift_by_register: 1;//should be false
    enum ShiftType shift_type: 2;
    uint8_t shift_amount: 5;
}__attribute__((packed));



int get_operand2(uint16_t secondOperand,
                 bool immediate,
                 bool flag,
                 uint32_t *operand2_val,
                 bool *carry_out);

#endif //SRC_OPERAND_TWO_UTIL_H
