//
// Created by fpn17 on 16/06/18.
//

#ifndef SRC_C3_CONTEXT_ID_REGISTER_H
#define SRC_C3_CONTEXT_ID_REGISTER_H


#include <stdint.h>

struct C3_context_id_register {
    uint8_t asid:8;
    uint32_t procid : 24;
}__attribute__((packed));

struct C3_context_id_register get_c3_context_id_register();

void set_c3_context_id_register(struct C3_context_id_register c3_context_id_register);

void init_c3_context_id_register();


#endif //SRC_C3_CONTEXT_ID_REGISTER_H
