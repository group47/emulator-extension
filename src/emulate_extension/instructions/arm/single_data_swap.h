//
// Created by francis on 6/1/18.
//

#ifndef SRC_SINGLE_DATA_SWAP_H
#define SRC_SINGLE_DATA_SWAP_H


#include <stdint.h>
#include <stdbool.h>
#include "../../basic_typedefs.h"

struct SingleDataSwapInstruction {
    RegisterAddress Rm : 4;
    uint8_t filler1001_position7 : 4;
    uint8_t filler0000_position11 : 4;
    RegisterAddress Rd : 4;
    RegisterAddress Rn : 4;
    uint8_t filler00_position21 : 2;
    bool byteWordBit : 1;
    uint8_t filler00010_position27 : 5; // should be 00010
    enum Cond cond: 4;
}__attribute__((packed));

enum ExecutionExitCode execute_instruction_single_data_swap(struct SingleDataSwapInstruction);

#endif //SRC_SINGLE_DATA_SWAP_H
