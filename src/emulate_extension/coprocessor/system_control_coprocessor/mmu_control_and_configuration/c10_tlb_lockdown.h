//
// Created by qs4617 on 07/06/18.
//

#ifndef SRC_C10_TLB_LOCKDOWN_H
#define SRC_C10_TLB_LOCKDOWN_H

struct C10_tlb_lockdown_register {
    bool P : 1;
    uint32_t sbz_unp : 25;
    uint8_t victim : 3;
    uint8_t sbz : 3;
}__attribute__((packed));

enum ExecutionExitCode execute_tlb_lockdown_register(struct CoprocessorRegisterTransferInstruction);
#endif //SRC_C10_TLB_LOCKDOWN_H
