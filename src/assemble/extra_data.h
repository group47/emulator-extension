//
// Created by francis on 5/28/18.
//

#ifndef SRC_EXTRA_DATA_H
#define SRC_EXTRA_DATA_H

#include <stdint.h>

static uint32_t extra_data_location;
static uint32_t extra_data_i = 0;
static uint32_t extra_data[100];

uint32_t add_extra_data(uint32_t);
void write_extra_data(FILE *pFILE);
#endif //SRC_EXTRA_DATA_H
