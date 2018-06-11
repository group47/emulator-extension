//
// Created by qs4617 on 07/06/18.
//

#ifndef SRC_C6_WATCHPOINT_FAULT_ADDRESS_H
#define SRC_C6_WATCHPOINT_FAULT_ADDRESS_H

#include <stdint.h>

/*
 *
 *
 */
struct C6_watchpoint_fault_address_register {
    uint32_t address : 32;
}__attribute__((packed));

#endif //SRC_C6_WATCHPOINT_FAULT_ADDRESS_H

enum ExecutionExitCode execute_watchpoint_fault_address_register(struct CoprocessorRegisterTransferInstruction);
