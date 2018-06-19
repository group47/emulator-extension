//
// Created by parallels on 6/18/18.
//

#include "c7_cache_dirty_status_register.h"
#include <memory.h>
struct C7_cache_dirty_status_register get_cache_dirty_status_register() {
    return c7_cache_dirty_status_register;
}

enum ExecutionExitCode set_word_cache_dirty_status_register(Word word) {
    c7_cache_dirty_status_register = *((struct C7_cache_dirty_status_register*) &word);
    return OK;
}

void init_c7_cache_dirty_status_register() {
    memset(&c7_cache_dirty_status_register, 0, sizeof(struct C7_cache_dirty_status_register));
}