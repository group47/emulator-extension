//
// Created by qs4617 on 12/06/18.
//

#ifndef SRC_ADDRESS_H
#define SRC_ADDRESS_H

#include <stdint.h>


struct ModifiedVirtualAddressSd1 {
    uint16_t filler : 12;
    uint16_t second_level_table_index : 8;
    uint16_t first_level_table_index : 12;
}__attribute__((packed));

struct ModifiedVirtualAddressSd2 {
    uint16_t page_index : 16;
    uint8_t part_of_sd_index : 4;
    uint16_t fd_table_index : 12;
}__attribute__((packed));

struct ModifiedVirtualAddressFd {
    uint32_t section_index : 20;
    uint16_t first_level_table_index : 12;
}__attribute__((packed));

union ModifiedVirtualAddress {
    struct ModifiedVirtualAddressFd mvafd;
    struct ModifiedVirtualAddressSd1 mvasd1;
    struct ModifiedVirtualAddressSd2 mvasd2;
};

struct First_level_descriptor_address {
    uint8_t filler00: 2;
    uint16_t first_level_table_index: 12;
    uint32_t translation_base: 18;
}__attribute__((packed));

struct Second_level_descriptor_address {
    uint8_t filler00 : 2;
    uint16_t second_level_table_index : 8;
    uint32_t coarse_page_table_base_address : 12;
}__attribute__((packed));


struct PhysicalAddress_1MB_section {
    uint16_t section_index : 20;
    uint32_t section_base_address : 12;
}__attribute__((packed));

struct PhysicalAddress_large_page {
    uint16_t page_index : 16;
    uint16_t page_base_address : 16;
}__attribute__((packed));

struct PhysicalAddress_small_page {
    uint32_t page_index: 12;
    uint32_t page_base_address : 20;
}__attribute__((packed));

union PhysicalAddress {
    struct PhysicalAddress_1MB_section physicalAddress_1MB_section;
    struct PhysicalAddress_small_page physicalAddress_small_page;
    struct PhysicalAddress_large_page physicalAddress_large_page;
};

#endif //SRC_ADDRESS_H
