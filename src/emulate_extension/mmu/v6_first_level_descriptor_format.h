//
// Created by qs4617 on 11/06/18.
//

#ifndef SRC_V6_FIRST_LEVEL_DESCRIPTOR_FORMAT_H
#define SRC_V6_FIRST_LEVEL_DESCRIPTOR_FORMAT_H

#include <stdint.h>
#include <stdbool.h>

struct V6_fd_translation_fault00 {
    uint8_t filler00 : 2;
    uint32_t ignored : 30;
}__attribute__((packed));

struct V6_fd_coarse_page_table {
    uint8_t filler01 : 2;
    bool sbz_position2 : 1;
    bool ns : 1;
    bool sbz_position4 : 1;
    uint8_t domain : 4;
    bool p: 1;
    uint32_t coarse_page_table_base_address : 22;
}__attribute__((packed));

struct V6_fd_section {
    uint8_t filler10 : 2;
    bool B : 1;
    bool C : 1;
    bool xn : 1;
    uint8_t domain : 4;
    bool P : 1;
    uint8_t ap : 2;
    uint8_t tex : 3;
    bool apx : 1;
    bool s : 1;
    bool ng : 1;
    bool filler0_position18 : 1;
    bool ns : 1;
    uint8_t section_base_address : 12;
}__attribute__((packed));

struct V6_fd_supersection {
    uint8_t filler01 : 2;
    bool B : 1;
    bool C : 1;
    bool xn : 1;
    uint8_t domain : 4;
    bool P : 1;
    uint8_t ap : 2;
    uint8_t text : 3;
    bool apx : 1;
    bool s : 1;
    bool ng : 1;
    bool filler0 : 1;
    bool ns : 1;
    uint8_t sbz : 4;
    uint8_t supersection_base_address : 8;
}__attribute__((packed));

struct V6_fd_translation_fault11 {
    uint8_t filler11: 2;
    uint32_t reserved : 30;
}__attribute__((packed));

struct V6_first_level_descriptor {
    struct V6_fd_translation_fault00 v6_fd_translation_fault00;
    struct V6_fd_coarse_page_table v6_fd_coarse_page_table;
    struct V6_fd_section v6_fd_section;
    struct V6_fd_supersection v6_fd_supersection;
    struct V6_fd_translation_fault11;
}__attribute__((packed));

#endif //SRC_V6_FIRST_LEVEL_DESCRIPTOR_FORMAT_H
