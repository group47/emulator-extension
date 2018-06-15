//
// Created by francis on 5/27/18.
//

#ifndef EMULATE_SINGLE_DATA_TRANSFER_INSTRUCTION_H
#define EMULATE_SINGLE_DATA_TRANSFER_INSTRUCTION_H
struct SingleDataTransferInstruction {
  short offset:12;
  uint8_t Rd:4;
  uint8_t Rn:4;
  bool loadStore : 1;
  uint8_t filler2: 2;
  bool upBit:1;
  bool prePostIndexingBit:1;
  bool immediateOffset:1;
  uint8_t filler:2; //should be 0b01
  enum Cond cond:4;
}__attribute__((packed));
#include <stdbool.h>
#include "../emulate_dir/emulate_main.h"
int execute_instruction_single_data_transfer(struct EmulatorState *,
                                             const struct SingleDataTransferInstruction);

#endif //EMULATE_SINGLE_DATA_TRANSFER_INSTRUCTION_H
