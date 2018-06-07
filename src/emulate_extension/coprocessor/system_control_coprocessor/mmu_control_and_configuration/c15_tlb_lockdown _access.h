//
// Created by qs4617 on 07/06/18.
//

#ifndef SRC_C15_TLB_LOCKDOWN_ACCESS_H
#define SRC_C15_TLB_LOCKDOWN_ACCESS_H


struct C15_tlb_lockdown_index_register {
    uint8_t index : 3;
    uint32_t unp_sbz : 29;
}__attribute__((packed));


struct C15_tlb_lockdown_va_register {
    uint8_t asid : 8;
    bool sbz_size2_position8 : 1;
    bool G : 1;
    uint8_t sbz : 2;
    uint32_t va : 20;
}__attribute__((packed));


struct C15_tlb_lockdown_pa_register {
    bool V : 1;
    uint8_t ap : 2;
    bool apx : 1;
    uint8_t sbz_size2_position_5 : 2;
    uint8_t size : 2;
    bool nstid : 1;
    bool nsa : 1;
    uint8_t sbz_size2_position11 : 2;
    uint32_t pa : 20;
}__attribute__((packed));


struct C15_tlb_lockdown_attributes_register {
    bool S : 1;
    bool B : 1;
    bool C : 1;
    uint8_t tex : 3;
    bool xn : 1;
    uint8_t domain : 4;
    uint16_t sbz : 14;
    bool spv : 1;
    uint8_t ap1 : 2;
    uint8_t ap2 : 2;
    uint8_t ap3 : 2;
}__attribute__((packed));


enum ExecutionExitCode execute_tlb_lockdown_access_register(struct CoprocessorRegisterTransferInstruction);


#endif //SRC_C15_TLB_LOCKDOWN_ACCESS_H
