//
// Created by qs4617 on 07/06/18.
//

#ifndef SRC_C2_TRANSLATION_TABLE_BASE0_H
#define SRC_C2_TRANSLATION_TABLE_BASE0_H

#include <stdbool.h>
#include <stdint.h>

struct C2_translation_table_base_register0 {
    bool c : 1;
    bool s : 1;
    bool p : 1;
    uint8_t rgn : 2;
    uint8_t
};

#endif //SRC_C2_TRANSLATION_TABLE_BASE0_H
