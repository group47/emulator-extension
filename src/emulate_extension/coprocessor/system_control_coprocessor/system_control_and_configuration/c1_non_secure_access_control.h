//
// Created by qs4617 on 07/06/18.
//

#ifndef SRC_C1_NON_SECURE_ACCESS_CONTROL_H
#define SRC_C1_NON_SECURE_ACCESS_CONTROL_H

#include <stdbool.h>
#include <stdint.h>
#include "../../../instructions/arm/coprocessor_register_transfer.h"

struct C1_none_secure_access_control_register {
    bool cp0 : 1;
    bool cp1 : 1;
    bool cp2 : 1;
    bool cp3 : 1;
    bool cp4 : 1;
    bool cp5 : 1;
    bool cp6 : 1;
    bool cp7 : 1;
    bool cp8 : 1;
    bool cp9 : 1;
    bool cp10 : 1;
    bool cp11 : 1;
    bool cp12 : 1;
    bool cp13 : 1;
    uint8_t sbz_size2_position_15 : 2;
    bool cl : 1;
    bool tl : 1;
    bool dma : 1;
    uint16_t sbz_size13_position_31 : 13;
}__attribute__((packed));

enum ExecutionExitCode execute_none_secure_access_control_register(struct CoprocessorRegisterTransferInstruction);

#endif //SRC_C1_NON_SECURE_ACCESS_CONTROL_H
