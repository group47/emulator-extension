//
// Created by qs4617 on 07/06/18.
//

#ifndef SRC_C6_INSTRUCTION_FAULT_ADDRESS_H
#define SRC_C6_INSTRUCTION_FAULT_ADDRESS_H

#include <stdint.h>

/*
 * hold the address of instructions that cause a
 * prefetch abort
 */

struct C6_instruction_fault_address_register {
    uint32_t address : 32;
}__attribute__((packed));

#endif //SRC_C6_INSTRUCTION_FAULT_ADDRESS_H

enum ExecutionExitCode execute_instruction_fault_address_register(struct CoprocessorRegisterTransferInstruction);
