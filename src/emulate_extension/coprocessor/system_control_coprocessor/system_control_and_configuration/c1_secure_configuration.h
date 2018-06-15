//
// Created by qs4617 on 07/06/18.
//

#ifndef SRC_C1_SECURE_CONFIGURATION_H
#define SRC_C1_SECURE_CONFIGURATION_H

#include <stdbool.h>
#include <stdint.h>
#include "../../../instructions/arm/coprocessor_register_transfer.h"

struct C1_secure_configuration_register {
    bool ns : 1;
    bool irq : 1;
    bool fiq : 1;
    bool ea : 1;
    bool rw : 1;
    bool aw : 1;
    bool net : 1;
    uint32_t sbz : 25;
} __attribute__((packed));

enum ExecutionExitCode execute_secure_configuration_register(struct CoprocessorRegisterTransferInstruction);
#endif //SRC_C1_SECURE_CONFIGURATION_H
