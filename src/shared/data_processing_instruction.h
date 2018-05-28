//
// Created by francis on 5/27/18.
//

#ifndef EMULATE_DATA_PROCESSING_INSTRUCTION_H
#define EMULATE_DATA_PROCESSING_INSTRUCTION_H

#include <malloc.h>
#include <stdbool.h>
#include "cpsr_overflow_detection.h"
#include "instructions.h"
#include "emulate_main.h"
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
                                        const struct DataProcessingInstruction);
#endif //EMULATE_DATA_PROCESSING_INSTRUCTION_H