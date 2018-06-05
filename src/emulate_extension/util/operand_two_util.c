//
// Created by francis on 6/2/18.
//

#include <stdint.h>
#include <stdbool.h>
#include <x86intrin.h>
#include <assert.h>
#include "operand_two_util.h"
#include "../state/emulator_state.h"


/*TODO: check if shift operator is correctly implemented (could be arithmetic instead of logical)
 */
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
    uint8_t shift_amount;
    enum ShiftType shift_type;
    if (immediateFalse.shift_by_register) {
      struct ImmediateFalseShiftByRegisterTrue
          shiftByRegister = *(struct ImmediateFalseShiftByRegisterTrue *) &secondOperand;

      assert(shiftByRegister.filler0 == 0b0);
      assert(shiftByRegister.Rs != PC_ADDRESS);

      shift_amount = (uint8_t) (get_word_from_register(shiftByRegister.Rs) & 0xff); //last byte//todo is this correct
      shift_type = shiftByRegister.shift_type;
      *operand2_val = get_word_from_register(shiftByRegister.Rm);
    } else {
      shift_amount = immediateFalse.shift_amount;
      shift_type = immediateFalse.shift_type;
      *operand2_val = get_word_from_register(immediateFalse.Rm);
    }

    //compute immediate false's value
    if (shift_amount == 0) {
      *carry_out = getCPSR().C;
    } else if (shift_amount > 0) {
      uint32_t ar_bit;
      switch (shift_type) {
        case lsl:
          if (shift_amount < 32) {
            *operand2_val <<= shift_amount - 1;
            *carry_out = (*operand2_val >> 31) != 0;
            *operand2_val <<= 1;
          } else {
            *operand2_val = 0;
            *carry_out = (shift_amount > 32) || ((*operand2_val & 0x1) != 0);
          }
          break;
        case lsr:
          if (shift_amount < 32) {
            *operand2_val >>= shift_amount - 1;
            *carry_out = (*operand2_val & 0x1) != 0;
            *operand2_val >>= 1;
          } else {
            *operand2_val = 0;
            *carry_out = (shift_amount > 32) || (((*operand2_val >> 31) & 0x1) != 0);
          }
          break;
        case asr:
          ar_bit = *operand2_val & (0b1 << 31);
          if (shift_amount < 32) {
            for (int i = 0; i < shift_amount - 1; ++i) {
              *operand2_val = (*operand2_val >> 1) | ar_bit;
            }
            *carry_out = (*operand2_val & 0x1) != 0;
            *operand2_val = (*operand2_val >> 1) | ar_bit;
          } else {
            *operand2_val = ar_bit ? 0xffffffff : 0x0;
            *carry_out = ((ar_bit >> 31) & 0x1) != 0;
          }
          break;
        case ror:
          shift_amount %= 32;
          if (shift_amount == 0) {
            *carry_out = ((*operand2_val >> 31) & 0x1) != 0;
          } else {
            *operand2_val = __rord(*operand2_val, shift_amount - 1);
            *carry_out = (*operand2_val & 0x1) != 0;
            *operand2_val = __rord(*operand2_val, 1);
          }
          break;
        default: assert(false);
      }
    } else {
      assert(false);
    }
    //*carry_out <<= 29;
  }
  return OK;

}
