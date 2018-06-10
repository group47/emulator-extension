//
// Created by fpn17 on 02/06/18.
//

#ifndef SRC_LOAD_STORE_REGISTER_OFFSET_H
#define SRC_LOAD_STORE_REGISTER_OFFSET_H

#include <stdbool.h>
#include "../../basic_typedefs.h"
#include "../../util/common_enums.h"

struct LoadStoreRegisterOffset {
    RegisterAddress Rd:3;
    RegisterAddress Rb:3;
    RegisterAddress Ro:3;
    bool filler0 : 1;
    bool load_byte : 1;
    enum LoadStore loadStore: 1;
    uint8_t filler0101 : 4;
}__attribute__((packed));

enum ExecutionExitCode execute_instruction_load_store_register_offset(struct LoadStoreRegisterOffset instruction);

#endif //SRC_LOAD_STORE_REGISTER_OFFSET_H
