//
// Created by qs4617 on 07/06/18.
//

#ifndef SRC_C5_INSTRUCTION_FAULT_STATUS_H
#define SRC_C5_INSTRUCTION_FAULT_STATUS_H

#include <stdint.h>
#include <stdbool.h>

struct C5_instruction_fault_status {
    uint8_t status : 4;
    uint8_t unp_sbz_size6_position9 : 6;
    bool filler0_posisiton10 : 1;
    bool sbz : 1;
    bool sd : 1;
    uint32_t unp_sbz_size19_position31 : 19;
}__attribute__((packed));

#endif //SRC_C5_INSTRUCTION_FAULT_STATUS_H
