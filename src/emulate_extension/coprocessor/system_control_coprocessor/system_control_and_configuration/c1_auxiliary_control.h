//
// Created by qs4617 on 07/06/18.
//

#ifndef SRC_C1_AUXILIARY_CONTROL_H
#define SRC_C1_AUXILIARY_CONTROL_H

#include <stdbool.h>
#include <stdint.h>

struct C1_auxiliary_control_register {
    bool rs : 1;
    bool db : 1;
    bool sb : 1;
    bool tr : 1;
    bool ra : 1;
    bool rv : 1;
    bool cz : 1;
    uint32_t sbz_unp : 21;
    bool phd : 1;
    bool bfd : 1;
    bool fsd : 1;
    bool fio : 1;
}__attribute__((packed));
#endif //SRC_C1_AUXILIARY_CONTROL_H
