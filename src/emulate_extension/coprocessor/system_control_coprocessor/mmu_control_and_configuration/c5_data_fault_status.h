//
// Created by qs4617 on 07/06/18.
//

#ifndef SRC_C5_DATA_FAULT_H
#define SRC_C5_DATA_FAULT_H

#include <stdint.h>
#include <stdbool.h>

struct C5_data_fault_status {
    uint8_t status : 4;
    uint8_t domain : 4;
    uint8_t filler00_posisiton9 : 2;
    bool s : 1;
    bool rw : 1;
    bool sd : 1;
    uint32_t unp_sbz : 19;
}__attribute__((packed));
#endif //SRC_C5_DATA_FAULT_H
