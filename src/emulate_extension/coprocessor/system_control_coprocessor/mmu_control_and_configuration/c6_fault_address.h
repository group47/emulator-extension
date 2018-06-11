//
// Created by qs4617 on 07/06/18.
//

#ifndef SRC_C6_FAULT_ADDRESS_H
#define SRC_C6_FAULT_ADDRESS_H

#include <stdint.h>


/*
 * holds the modified virtual address of the fault
 * when the precise abort occurs
 */
struct C6_fault_address_register {
    uint32_t mva : 32;
}__attribute__((packed));

#endif //SRC_C6_FAULT_ADDRESS_H


enum ExecutionExitCode execute_fault_address_register(struct CoprocessorRegisterTransferInstruction);