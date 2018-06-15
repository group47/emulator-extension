//
// Created by fpn17 on 12/06/18.
//

#include "c0_cache_type_register.h"

static struct C0_cache_type_register c0_cache_type_register;

struct C0_cache_type_register get_C0_cache_type_register() {
    c0_cache_type_register.CType = 0b1110;
    c0_cache_type_register.S = 1;
    c0_cache_type_register.P_Dsize = 0;
    c0_cache_type_register.P_Isize = 0;
    c0_cache_type_register.Assoc_Dsize = 0b010;
    c0_cache_type_register.Assoc_Isize = 0b010;
    c0_cache_type_register.filler_000 = 000;
    c0_cache_type_register.Len_Dsize = 0b10;
    c0_cache_type_register.Len_Isize = 0b10;
    c0_cache_type_register.M_Dsize = 0;
    c0_cache_type_register.M_Isize = 0;
    c0_cache_type_register.Size_Dsize = 0b000;
    c0_cache_type_register.Size_Isize = 0b000;
    return c0_cache_type_register;
}