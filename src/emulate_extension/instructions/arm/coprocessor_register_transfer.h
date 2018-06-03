//
// Created by fpn17 on 02/06/18.
//

#ifndef SRC_COPROCESSOR_REGISTER_TRANSFER_H
#define SRC_COPROCESSOR_REGISTER_TRANSFER_H

#include <stdint.h>
#include <stdbool.h>
#include "../../util/common_enums.h"

struct CoProcessorRegisterTransfer{
    uint8_t  CRm : 4;
    bool filler1:1;
    uint8_t CP : 3;
    uint8_t CPNum : 4;
    uint8_t Rd : 3;
    uint8_t CRn: 4;
    enum LoadStore loadStore : 1;
    uint8_t CPOpc : 3;
    uint8_t filler1110:4;
    enum Cond cond:4;
};

enum ExecutionExitCode execute_copprocessor_register_transfer(struct CoProcessorRegisterTransfer instruction);

#endif //SRC_COPROCESSOR_REGISTER_TRANSFER_H
