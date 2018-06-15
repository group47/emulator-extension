//
// Created by qs4617 on 07/06/18.
//

#ifndef SRC_C10_MEMORY_REGION_REMAP_H
#define SRC_C10_MEMORY_REGION_REMAP_H

// todo: decide unifying behaviour for different mode of register
struct C10_memory_remap_region_register {
    uint32_t content : 32;
}__attribute__((packed));


enum ExecutionExitCode execute_remap_register(struct CoprocessorRegisterTransferInstruction);

#endif //SRC_C10_MEMORY_REGION_REMAP_H
