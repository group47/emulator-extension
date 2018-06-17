//
// Created by ryro on 2018/5/26.
//

#include <stdint.h>
#include "binary_file_writer.h"


// Assuming the file pointer is pointed to the correct position
void binary_file_writer32(FILE *fpOutput, int32_t binaryFormat) {
    uint8_t bytes[4];
    for (int i = 0; i < 4; i++) {
        bytes[i] = (uint8_t) ((binaryFormat >> (8 * i)) & 0xff);
    }
    fwrite(bytes, 4, 1, fpOutput);
}
