//
// Created by qs4617 on 13/06/18.
//

#ifndef SRC_SECOND_LEVEL_DESCRIPTOR_H
#define SRC_SECOND_LEVEL_DESCRIPTOR_H

#include <stdint.h>
#include <stdbool.h>

struct V6_sd_translation_fault {
    uint8_t filler00: 2;
    uint32_t ignored : 30;
}__attribute__((packed));

struct V6_sd_large_page {
    uint8_t filler01: 2;
    bool B: 1;
    bool C : 1;
    uint8_t ap : 2;
    uint8_t sbz : 3;
    bool apx : 1;
    bool s : 1;
    bool ng : 1;
    uint8_t tex : 3;
    bool xn : 1;
    uint16_t large_page_base_address : 16;
}__attribute__((packed));

struct V6_sd_extended_small_page {
    bool xn : 1;
    bool filler0: 1;
    bool B: 1;
    bool C: 1;
    uint8_t ap : 2;
    uint8_t tex : 3;
    bool apx : 1;
    bool s : 1;
    bool ng : 1;
    uint32_t extended_small_page_address : 20;
}__attribute__((packed));

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
    uint32_t small_page_base_address : 20;
}__attribute__((packed));

struct Backwards_sd_extended_small_page {
    uint8_t filler10 : 2;
    bool B : 1;
    bool C : 1;
    uint8_t tex : 4;
    uint8_t sbz : 3;
    uint32_t extended_small_page_base_address : 20;
}__attribute__((packed));


union Second_level_descriptor {
    struct V6_sd_extended_small_page v6_sd_extended_small_page;
    struct V6_sd_large_page v6_sd_large_page;
    struct V6_sd_translation_fault v6_sd_translation_fault;
    struct Backwards_sd_extended_small_page backwards_sd_extended_small_page;
    struct Backwards_sd_large_page backwards_sd_large_page;
    struct Backwards_sd_small_page backwards_sd_small_page;
    struct Backwards_sd_translation_fault backwards_sd_translation_fault;
};

#endif //SRC_SECOND_LEVEL_DESCRIPTOR_H
