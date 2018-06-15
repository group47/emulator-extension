//
// Created by francis on 5/27/18.
//

#ifndef EMULATE_DATA_PROCESSING_INSTRUCTION_H
#define EMULATE_DATA_PROCESSING_INSTRUCTION_H

#include <stdbool.h>
#include "../emulate_dir/emulate_main.h"
#include "instructions.h"

struct DataProcessingInstruction {
  uint16_t secondOperand : 12;
  uint8_t Rd:4;
  uint8_t Rn: 4;
  bool setConditionCodes: 1;
  enum OpCode opcode : 4;
  bool immediateOperand: 1;
  uint8_t filler: 2;//The value of the filler should be 0b000
  enum Cond cond : 4;
}__attribute__((packed));//the attribute is required for the compiler to properly place data types

int execute_instruction_data_processing(struct EmulatorState *,
                                        struct DataProcessingInstruction);
#endif //EMULATE_DATA_PROCESSING_INSTRUCTION_H
