//
// Created by francis on 5/28/18.
//

#include <stdio.h>
#include "extra_data.h"
#include "binary_file_writer.h"

static uint32_t extra_data_i = 0;
static uint32_t extra_data[100];


static uint32_t extra_data_location = (uint32_t) -1;

void set_extra_data_location(uint32_t val) {
    extra_data_location = val;
}

uint32_t add_extra_data(uint32_t val) {
    if (extra_data_location == (uint32_t) -1) {
        return -1;
    }
    extra_data[extra_data_i] = val;
    extra_data_i++;
    return extra_data_i - 1 + extra_data_location;
}

void write_extra_data(FILE *pFILE) {
    for (uint32_t i = 0; i < extra_data_i; ++i) {
        binary_file_writer32(pFILE, extra_data[i]);
    }
}