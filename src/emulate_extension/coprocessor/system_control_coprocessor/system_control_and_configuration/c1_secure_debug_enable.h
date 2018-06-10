//
// Created by qs4617 on 07/06/18.
//

#ifndef SRC_C1_SECURE_DEBUG_ENABLE_H
#define SRC_C1_SECURE_DEBUG_ENABLE_H

#include <stdbool.h>
#include <stdint.h>
#include "../../../../emulate/emulate_main.h"
#include "../../../instructions/arm/coprocessor_register_transfer.h"

struct C1_secure_debug_enable_register {
    bool suiden : 1;
    bool suniden : 1;
    uint32_t sbz : 30;
}__attribute__((packed));


enum ExecutionExitCode execute_debug_enable_register(struct CoprocessorRegisterTransferInstruction);
#endif //SRC_C1_SECURE_DEBUG_ENABLE_H
