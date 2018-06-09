//
// Created by qs4617 on 02/06/18.
//

#ifndef SRC_HI_REGISTER_OPERATIONS_BRANCH_EXCHANGE_H
#define SRC_HI_REGISTER_OPERATIONS_BRANCH_EXCHANGE_H

#include <stdint.h>
#include <stdbool.h>
#include "../../util/common_enums.h"

struct HiRegisterOperationsBranchExchangeInstruction {
    uint8_t RdHd : 3;
    uint8_t RsHs : 3;
    bool H2 : 1;
    bool H1 : 1;
    uint8_t Op : 2;
    uint8_t filler010001_position15 : 6;
};

enum ExecutionExitCode
execute_instruction_hi_register_operations_branch_exchange(struct HiRegisterOperationsBranchExchangeInstruction);

#endif //SRC_HI_REGISTER_OPERATIONS_BRANCH_EXCHANGE_H
