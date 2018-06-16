//
// Created by fpn17 on 16/06/18.
//

#include <assert.h>
#include <memory.h>
#include "c3_context_id_register.h"
#include "../../../state/emulator_state.h"

static struct C3_context_id_register c3_context_id_register;

struct C3_context_id_register get_c3_context_id_register() {
    assert(get_operating_mode() != usr);
    return c3_context_id_register;
}

void set_c3_context_id_register(struct C3_context_id_register to_set) {
    assert(get_operating_mode() != usr);
    c3_context_id_register = to_set;
}

void init_c3_context_id_register() {
    memset(&c3_context_id_register, 0, sizeof(struct C3_context_id_register));
}