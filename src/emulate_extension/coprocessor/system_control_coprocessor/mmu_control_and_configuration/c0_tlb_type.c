//
// Created by qs4617 on 07/06/18.
//

#include "c0_tlb_type.h"

struct C0_TLB_type_register {
    uint8_t U : 1;
    uint8_t sbz_unp_size7_position_7 : 7;
    uint8_t dlsize : 8;
    uint8_t ilsize : 8;
    uint8_t sbz_unp_size8_position_31 : 8;
}__attribute__((packed));

enum ExecutionExitCode execute_tlb_type_register(struct CoprocessorRegisterTransferInstruction);