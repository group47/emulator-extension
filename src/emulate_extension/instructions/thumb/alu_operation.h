//
// Created by fpn17 on 02/06/18.
//

#ifndef SRC_ALU_OPERATIONS_H
#define SRC_ALU_OPERATIONS_H

#include "../../basic_typedefs.h"

enum ThumbALUOpCode{
    AND_THUMB_ALU = 0b0000,
    EOR_THUMB_ALU = 0b0001,
    LSL_THUMB_ALU = 0b0010,
    LSR_THUMB_ALU = 0b0011,
    ASR_THUMB_ALU = 0b0100,
    ADC_THUMB_ALU = 0b0101,
    SBC_THUMB_ALU = 0b0110,
    ROR_THUMB_ALU = 0b0111,
    TST_THUMB_ALU = 0b1000,
    NEQ_THUMB_ALU = 0b1001,
    CMP_THUMB_ALU = 0b1010,
    CMN_THUMB_ALU = 0b1011,
    ORR_THUMB_ALU = 0b1100,
    MUL_THUMB_ALU = 0b1101,
    BIC_THUMB_ALU = 0b1110,
    MVN_THUMB_ALU = 0b1111
};

struct ALUOperation{
    RegisterAddress Rd:3;
    RegisterAddress Rs:3;
    enum ThumbALUOpCode Op:4;
    uint8_t filler010000:6;

}__attribute__((packed));

enum ExecutionExitCode execute_instruction_alu_operation(struct ALUOperation instruction);
#endif //SRC_ALU_OPERATIONS_H
