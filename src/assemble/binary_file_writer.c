//
// Created by ryro on 2018/5/26.
//

#include <stdint.h>
#include "binary_file_writer.h"


// Assuming the file pointer is pointed to the correct position
void binary_file_writer32(FILE* fpOutput, int32_t binaryFormat) {

    uint8_t bytes[4];
    bytes[0] = (uint8_t)(binaryFormat & 0xff);
    bytes[1] = (uint8_t)((binaryFormat >> 8) & 0xff);
    bytes[2] = (uint8_t)((binaryFormat >> 16) & 0xff);
    bytes[3] = (uint8_t)((binaryFormat >> 24) & 0xff);

    fwrite(bytes, 4, 1, fpOutput);

}

void binary_file_writer16(FILE* fpOutput, int16_t address) {
    unsigned char bytes[2];
    fwrite(bytes, 2, 1, fpOutput);
    // might need to write the address in reverse order
}