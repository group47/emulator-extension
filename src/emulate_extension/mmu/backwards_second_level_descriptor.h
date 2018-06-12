//
// Created by qs4617 on 11/06/18.
//

#ifndef SRC_BACKWARDS_SECOND_LEVEL_DESCRIPTOR_H
#define SRC_BACKWARDS_SECOND_LEVEL_DESCRIPTOR_H

#include <stdint.h>
#include <stdbool.h>

struct Backwards_sd_translation_fault {
    uint8_t filler00: 2;
    uint32_t ignored : 30;
}__attribute__((packed));

struct Backwards_sd_large_page {
    uint8_t filler01 : 2;
    bool B : 1;
    bool C : 1;
    uint8_t ap0 : 2;
    uint8_t ap1 : 2;
    uint8_t ap2 : 2;
    uint8_t ap3 : 2;
    uint8_t tex : 4;
    uint16_t large_page_base_address : 16;
}__attribute__((packed));

struct Backwards_sd_small_page {
    uint8_t filler10: 2;
    bool B : 1;
    bool C : 1;
    uint8_t ap0: 2;
    uint8_t ap1: 2;
    uint8_t ap2: 2;
    uint8_t ap3: 2;
    uint32_t large_page_base_address : 20;
}__attribute__((packed));

struct Backwards_sd_extended_small_page {
    uint8_t filler10 : 2;
    bool B : 1;
    bool C : 1;
    uint8_t tex : 4;
    uint8_t sbz : 3;
    uint32_t extended_small_page_base_address : 20;
}__attribute__((packed));


union Backwards_second_level_descriptor {
    struct Backwards_sd_translation_fault translation_fault;
    struct Backwards_sd_large_page large_page;
    struct Backwards_sd_small_page small_page;
    struct Backwards_sd_extended_small_page extended_small_page;
};


#endif //SRC_BACKWARDS_SECOND_LEVEL_DESCRIPTOR_H
