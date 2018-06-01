//
// Created by francis on 5/27/18.
//

#ifndef EMULATE_MULTIPLY_INSTRUCTION_H
#define EMULATE_MULTIPLY_INSTRUCTION_H
struct MultiplyInstruction {
  uint8_t Rm : 4;
  uint8_t filler2:4;//should equal 0b1001
  uint8_t Rs:4;
  uint8_t Rn:4;
  uint8_t destinationRegister:4;
  bool setConditionCodes: 1;
  bool accumulate: 1;
  uint8_t filler : 6;//should be 0b000000
  enum Cond cond : 4;
}__attribute__((packed));
#include <stdbool.h>
#include "emulate_main.h"
int execute_instruction_multiply(struct CPUState *,
                                 const struct MultiplyInstruction);
#endif //EMULATE_MULTIPLY_INSTRUCTION_H
