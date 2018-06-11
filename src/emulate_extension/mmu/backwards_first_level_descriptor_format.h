//
// Created by qs4617 on 11/06/18.
//

#ifndef SRC_BACKWARDS_FIRST_LEVEL_DESCRIPTOR_FORMAT_H
#define SRC_BACKWARDS_FIRST_LEVEL_DESCRIPTOR_FORMAT_H

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
    bool filler0 : 1;
    uint8_t domain : 4;
    bool P : 1;
    uint8_t ap : 2;
    uint8_t tex : 3;
    uint8_t sbz : 3;
    bool filler0 : 1;
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
    bool filler0 : 1;
    bool ns : 1;
    uint8_t sbz_size3_position23 : 3;
    uint8_t supersection_base_address : 8;
}__attribute__((packed));

struct Backwards_fd_reserved {
    uint8_t filler11 : 2;
    uint32_t nothing : 30;
}__attribute__((packed));


union Backwards_first_level_descriptor {
    struct Backwards_fd_ignored ignored;
    struct Backwards_fd_course_page_table course_page_table;
    struct Backwards_fd_section section;
    struct Backwards_fd_supersection supersection;
    struct Backwards_fd_reserved reserved;
};

#endif //SRC_BACKWARDS_FIRST_LEVEL_DESCRIPTOR_FORMAT_H
