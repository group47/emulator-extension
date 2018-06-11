//
// Created by qs4617 on 11/06/18.
//

#ifndef SRC_BACKWARDS_SECOND_LEVEL_DESCRIPTOR_H
#define SRC_BACKWARDS_SECOND_LEVEL_DESCRIPTOR_H

struct Backwards_sd_translation_fault {
    uint8_t filler00: 2;
    uint8_t ignored : 30;
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

};

struct Backwards_sd_extended_small_page {

};


#endif //SRC_BACKWARDS_SECOND_LEVEL_DESCRIPTOR_H
