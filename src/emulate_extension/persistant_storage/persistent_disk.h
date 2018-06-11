//
// Created by fpn17 on 10/06/18.
//

#ifndef SRC_PERSISTENT_DISK_H
#define SRC_PERSISTENT_DISK_H

#include <stdint.h>

struct Disk {
    uint32_t *ptr;
    uint64_t size;
};

uint32_t get_from_index(uint64_t index);

void set_at_index(uint64_t index, uint32_t val);

#endif //SRC_PERSISTENT_DISK_H
