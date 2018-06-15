//
// Created by qs4617 on 07/06/18.
//

#ifndef SRC_C8_TLB_OPERATIONS_H
#define SRC_C8_TLB_OPERATIONS_H

// todo: try to combine two access mode of register

static bool BY_MVA; // access mode for accessing register
                    // different access mode lead to different field of register


struct C8_tlb_operations_register {
    uint8_t asid : 8;
    uint32_t mva_sbz_or_sbz : 24;
}__attribute__((packed));

#endif //SRC_C8_TLB_OPERATIONS_H
