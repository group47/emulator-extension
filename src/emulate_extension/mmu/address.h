//
// Created by qs4617 on 12/06/18.
//

#ifndef SRC_ADDRESS_H
#define SRC_ADDRESS_H

#include <stdint.h>

struct ModifiedVirtualAddress {
    uint32_t section_index : 20;
    uint32_t first_level_table_index : 12;
}__attribute__((packed));



#endif //SRC_ADDRESS_H
