//
// Created by fpn17 on 15/06/18.
//

#ifndef SRC_TOKEN_H
#define SRC_TOKEN_H

#include <stdint.h>
#include <stdbool.h>

struct Token {
    struct InstructionInfo *instructionInfo;
    char *label;
    uint8_t Rn;
    uint8_t Rd;
    uint8_t Rs;
    uint8_t Rm;
    uint16_t operand2 : 12;
    uint32_t offset;
    bool operand2IsImmediate;
    bool offsetIsImmediate;
    bool offsetIsNegative;
    bool isPreIndexing;
    bool use_extra_data;
};


#endif //SRC_TOKEN_H
