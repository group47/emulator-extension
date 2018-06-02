//
// Created by qs4617 on 02/06/18.
//

#ifndef SRC_BRANCH_AND_EXCHANGE_H
#define SRC_BRANCH_AND_EXCHANGE_H

#include <stdint.h>
#include "../../util/common_enums.h"

struct BranchAndExchangeInstruction {
    uint8_t Rn : 4;
    uint32_t filler0001_0010_1111_1111_1111_0001_position27 : 24;
    enum Cond cond :4;
}__attribute__((packed));

enum ExecutionExitCode execute_instruction_branch_and_exchange_instruction(struct BranchAndExchangeInstruction);
#endif //SRC_BRANCH_AND_EXCHANGE_H
