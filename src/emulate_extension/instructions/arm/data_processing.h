//
// Created by francis on 6/1/18.
//

#ifndef SRC_DATA_PROCESSING_H
#define SRC_DATA_PROCESSING_H

#include "../../util/common_enums.h"
#include "../../basic_typedefs.h"
#include <stdbool.h>

#define IMMEDIATE_BIT_FLAG_DATA_PROCESSING true

enum OpCode {
    and = 0b0000,
    eor = 0b0001,
    sub = 0b0010,
    rsb = 0b0011,
    add = 0b0100,
    adc = 0b0101,
    sbc = 0b0110,
    rsc = 0b0111,
    tst = 0b1000,
    teq = 0b1001,
    cmp = 0b1010,
    cmn = 0b1011,
    orr = 0b1100,
    mov = 0b1101,
    bic = 0b1110,
    mvn = 0b1111
};

struct DataProcessingInstruction {
  uint16_t secondOperand : 12;
  RegisterAddress Rd:4;
  RegisterAddress Rn: 4;
  bool setConditionCodes: 1;
  enum OpCode opcode : 4;//todo not all opcode done, needs adding
  bool immediateOperand: 1;
  uint8_t filler: 2;//The value of the filler should be 0b00
  enum Cond cond : 4;
}__attribute__((packed));//the attribute is required for the compiler to properly place data types

enum ExecutionExitCode execute_instruction_data_processing(struct DataProcessingInstruction);



#endif //SRC_DATA_PROCESSING_H
