//
// Created by francis on 6/1/18.
//

#ifndef SRC_MULTIPLY_LONG_H
#define SRC_MULTIPLY_LONG_H

#include <stdbool.h>
#include "../../basic_typedefs.h"
#include "../../util/common_enums.h"

struct MultiplyLongInstruction {
    RegisterAddress Rm    : 4;
    uint8_t filler1001       : 4; //should equal 0b1001
    RegisterAddress Rs    : 4;
    RegisterAddress RdLo  : 4;
    RegisterAddress RdHi  : 4;
    bool setConditionCodes: 1;
    bool accumulate       : 1;
    bool signedVal        : 1;
    uint8_t filler00001        : 5; //should be 0b00001
    enum Cond cond        : 4;
}__attribute__((packed));

enum ExecutionExitCode execute_instruction_multiply_long(const struct MultiplyLongInstruction);

#endif //SRC_MULTIPLY_LONG_H
