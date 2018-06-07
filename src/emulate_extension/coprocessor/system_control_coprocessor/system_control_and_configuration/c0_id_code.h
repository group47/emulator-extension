//
// Created by qs4617 on 07/06/18.
//

#ifndef SRC_C0_ID_CODE_H
#define SRC_C0_ID_CODE_H

#include <stdint.h>
#include "../../../util/common_enums.h"
#include "../../../instructions/arm/coprocessor_register_transfer.h"

struct C0_main_id_register {
    uint8_t revision : 4;
    uint16_t primary_part_number : 12;
    uint8_t architecture : 4;
    uint8_t variant_number : 4;
    uint16_t implementor : 8;
}__attribute__((packed));

enum ExecutionExitCode execute_co_main_id_register(struct CoprocessorRegisterTransferInstruction);

#endif //SRC_C0_ID_CODE_H
