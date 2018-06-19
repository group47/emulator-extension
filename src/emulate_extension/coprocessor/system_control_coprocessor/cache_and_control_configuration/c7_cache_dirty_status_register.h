//
// Created by parallels on 6/18/18.
//

#ifndef SRC_C7_CACHE_DIRTY_STATUS_REGISTER_H
#define SRC_C7_CACHE_DIRTY_STATUS_REGISTER_H

#include <stdbool.h>
#include <stdint.h>
#include "../../../util/common_enums.h"
#include "../../../basic_typedefs.h"

static struct C7_cache_dirty_status_register c7_cache_dirty_status_register;

struct C7_cache_dirty_status_register {
    bool C : 1;
    uint32_t raz : 31;
}__attribute__((packed));

struct C7_cache_dirty_status_register get_cache_dirty_status_register();

enum ExecutionExitCode set_word_cache_dirty_status_register(Word);

void init_c7_cache_dirty_status_register();

#endif //SRC_C7_CACHE_DIRTY_STATUS_REGISTER_H
