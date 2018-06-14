//
// Created by qs4617 on 13/06/18.
//

#ifndef SRC_FIRST_LEVEL_DESCRIPTOR_H
#define SRC_FIRST_LEVEL_DESCRIPTOR_H

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
    uint16_t section_base_address : 12;
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


struct Backwards_fd_ignored {
    uint8_t filler00 : 2;
    uint32_t ignored : 30;
}__attribute__((packed));

struct Backwards_fd_course_page_table {
    uint8_t filler01 : 2;
    bool sbz_position2 : 1;
    bool ns : 1;
    bool sbz_position4 : 1;
    uint8_t domain : 4;
    bool p: 1;
    uint32_t coarse_page_table_base_address : 22;
}__attribute__((packed));

struct Backwards_fd_section {
    uint8_t filler10 : 2;
    bool B : 1;
    bool C : 1;
    bool filler0_position4 : 1;
    uint8_t domain : 4;
    bool P : 1;
    uint8_t ap : 2;
    uint8_t tex : 3;
    uint8_t sbz : 3;
    bool filler0_position18 : 1;
    bool ns : 1;
    uint8_t section_base_address : 12;
}__attribute__((packed));

struct Backwards_fd_supersection {
    uint8_t filler10 : 2;
    bool B : 1;
    bool C : 1;
    bool filler0 : 1;
    uint8_t domain : 4;
    bool P : 1;
    uint8_t ap : 2;
    uint8_t tex : 3;
    uint8_t sbz_sized3_position17 : 3;
    bool filler1 : 1;
    bool ns : 1;
    uint8_t sbz_size3_position23 : 3;
    uint8_t supersection_base_address : 8;
}__attribute__((packed));

struct Backwards_fd_reserved {
    uint8_t filler11 : 2;
    uint32_t nothing : 30;
}__attribute__((packed));


union First_level_descriptor {
    struct V6_fd_section v6_fd_section;
    struct V6_fd_coarse_page_table v6_fd_coarse_page_table;
    struct V6_fd_supersection v6_fd_supersection;
    struct V6_fd_translation_fault00 v6_fd_translation_fault00;
    struct V6_fd_translation_fault11 v6_fd_translation_fault11;
    struct Backwards_fd_course_page_table backwards_fd_course_page_table;
    struct Backwards_fd_ignored backwards_fd_ignored;
    struct Backwards_fd_reserved backwards_fd_reserved;
    struct Backwards_fd_section backwards_fd_section;
    struct Backwards_fd_supersection backwards_fd_supersection;
};

#endif //SRC_FIRST_LEVEL_DESCRIPTOR_H
