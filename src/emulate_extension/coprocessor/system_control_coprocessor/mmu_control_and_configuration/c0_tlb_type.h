//
// Created by qs4617 on 07/06/18.
//

#ifndef SRC_C0_TLB_TYPE_H
#define SRC_C0_TLB_TYPE_H

#include <stdbool.h>
#include <stdint.h>

struct C0_tlb_type_register {
    bool u : 1;
    uint8_t sbz_unp_size7_position_7 : 7;
    uint8_t dlsize : 8;
    uint8_t ilsize : 8;
    uint8_t sbz_unp_size8_posistion_: 8;
}__attribute__((packed));



#endif //SRC_C0_TLB_TYPE_H
