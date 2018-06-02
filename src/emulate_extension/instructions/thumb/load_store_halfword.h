//
// Created by fpn17 on 02/06/18.
//

#ifndef SRC_LOAD_STORE_HALFWORD_H
#define SRC_LOAD_STORE_HALFWORD_H


#include <stdint.h>
#include "../../basic_typedefs.h"
#include "../../util/common_enums.h"

struct LoadStoreHalfWord{
    RegisterAddress Rd: 3;
    RegisterAddress Rb: 3;
    uint8_t offset5 : 5;
    enum LoadStore loadStore: 1;
    uint8_t filler1000 : 4;
};

#endif //SRC_LOAD_STORE_HALFWORD_H
