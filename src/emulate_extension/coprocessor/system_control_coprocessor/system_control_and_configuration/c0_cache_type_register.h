//
// Created by fpn17 on 12/06/18.
//

#ifndef SRC_C0_CACHE_TYPE_REGISTER_H
#define SRC_C0_CACHE_TYPE_REGISTER_H


#include <stdint.h>
#include <stdbool.h>

struct C0_cache_type_register {
    uint8_t Len_Isize : 2;
    bool M_Isize : 1;
    uint8_t Assoc_Isize: 3;
    uint8_t Size_Isize :4;
    bool filler_Isize : 1;
    bool P_Isize: 1;
    uint8_t Len_Dsize : 2;
    bool M_Dsize : 1;
    uint8_t Assoc_Dsize: 3;
    uint8_t Size_Dsize :4;
    bool filler_Dsize : 1;
    bool P_Dsize: 1;
    bool S : 1;
    uint8_t CType : 3;
    uint8_t filler_000: 3;
};

struct C0_cache_type_register get_C0_cache_type_register();

#endif //SRC_C0_CACHE_TYPE_REGISTER_H
