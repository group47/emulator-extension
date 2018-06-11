//
// Created by qs4617 on 07/06/18.
//

#ifndef SRC_C15_PERIPHERAL_PORT_MEMORY_REMAP_H
#define SRC_C15_PERIPHERAL_PORT_MEMORY_REMAP_H

struct C15_peripheral_port_memory_remap_register {
    uint8_t size : 5;
    uint8_t unp_sbz : 7;
    uint32_t base_address : 20;
}__attribute__((packed));


enum ExecutionExitCode execute_peripheral_port_memory_remap_register(struct CoprocessorRegisterTransferInstruction);

#endif //SRC_C15_PERIPHERAL_PORT_MEMORY_REMAP_H
