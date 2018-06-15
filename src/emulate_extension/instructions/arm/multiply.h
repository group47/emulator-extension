//
// Created by francis on 6/1/18.
//

#ifndef SRC_MULTIPLY_H
#define SRC_MULTIPLY_H

#include <stdbool.h>
#include "../../basic_typedefs.h"
#include "../../util/common_enums.h"

struct MultiplyInstruction {
    RegisterAddress Rm    : 4;
    uint8_t filler1001       : 4; //should equal 0b1001
    RegisterAddress Rs    : 4;
    RegisterAddress Rn    : 4;
    RegisterAddress Rd    : 4;
    bool setConditionCodes: 1;
    bool accumulate       : 1;
    uint8_t filler000000        : 6; //should be 0b000000
    enum Cond cond        : 4;
}__attribute__((packed));

enum ExecutionExitCode execute_instruction_multiply(const struct MultiplyInstruction);

#endif //SRC_MULTIPLY_H
