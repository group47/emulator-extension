//
// Created by qs4617 on 02/06/18.
//

#ifndef SRC_PUSH_POP_REGISTERS_H
#define SRC_PUSH_POP_REGISTERS_H

#include <stdint.h>
#include <stdbool.h>
#include "../../util/common_enums.h"

struct PushPopRegistersInstruction {
    uint8_t registerList : 8;
    bool PCLRBit : 1;
    uint8_t filler10_position10 : 2;
    enum LoadStore loadStoreBit: 1;
    uint8_t filler1011_position15 : 4;
}__attribute__((packed));

enum ExecutionExitCode execute_instruction_push_pop_registers(struct PushPopRegistersInstruction);

#endif //SRC_PUSH_POP_REGISTERS_H
