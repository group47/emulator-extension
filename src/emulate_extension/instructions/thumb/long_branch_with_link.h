//
// Created by mhl1817 on 02/06/18.
//

#ifndef SRC_LONG_BRANCH_WITH_LINK_H
#define SRC_LONG_BRANCH_WITH_LINK_H

#include <stdbool.h>
#include "../../basic_typedefs.h"
#include "../../util/common_enums.h"

struct LongBranchWithLinkInstruction {
    uint16_t offset   : 11;
    bool lowOffsetBit : 1;
    uint8_t filler1111    : 4; //1111
}__attribute__((packed));

enum ExecutionExitCode execute_instruction_long_branch_with_link(const struct LongBranchWithLinkInstruction);


#endif //SRC_LONG_BRANCH_WITH_LINK_H
