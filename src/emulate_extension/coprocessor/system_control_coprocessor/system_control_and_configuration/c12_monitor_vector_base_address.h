//
// Created by qs4617 on 07/06/18.
//

#ifndef SRC_C12_MONITOR_VECTOR_BASE_ADDRESS_H
#define SRC_C12_MONITOR_VECTOR_BASE_ADDRESS_H

#include <stdint.h>
#include "../../../instructions/arm/coprocessor_register_transfer.h"

struct C12_monitor_vector_base_address_register {
    uint8_t sbz : 5;
    uint32_t monitor_vector_base_address_register : 27;
}__attribute__((packed));

enum ExecutionExitCode execute_monitor_vector_base_address_register(struct CoprocessorRegisterTransferInstruction);

#endif //SRC_C12_MONITOR_VECTOR_BASE_ADDRESS_H
