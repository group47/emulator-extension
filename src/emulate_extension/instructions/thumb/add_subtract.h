//
// Created by francis on 6/2/18.
//

#ifndef SRC_ADD_SUBTRACT_H
#define SRC_ADD_SUBTRACT_H

#include <stdbool.h>
#include "../../basic_typedefs.h"

enum AddSubtractOp{
  ADD = 0,SUB = 1
};

struct AddSubtractInstruction{
  RegisterAddress Rd : 4;
  RegisterAddress Rs : 4;
  uint8_t RnOffset3: 3;
  enum AddSubtractOp op: 1;
  bool immediate : 1;
  uint8_t shouldBe0b00011: 5;
}__attribute__((packed));

enum ExecutionExitCode execute_instruction_add_subtract(const struct AddSubtractInstruction instruction);

#endif //SRC_ADD_SUBTRACT_H
