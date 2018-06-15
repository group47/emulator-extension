//
// Created by qs4617 on 02/06/18.
//

#ifndef SRC_UNDEFINED_H
#define SRC_UNDEFINED_H

#include <stdint.h>
#include "../../util/common_enums.h"

struct UndefinedInstruction {
    uint8_t undefined2 : 4;
    uint8_t filler1_position4 : 1;
    uint32_t undefined1 : 20;
    uint8_t filler011_position27 : 3;
    enum Cond cond : 4;
}__attribute__((packed));

enum ExecutionExitCode execute_instruction_undefined(struct UndefinedInstruction);

#endif //SRC_UNDEFINED_H
