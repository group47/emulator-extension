//
// Created by francis on 5/27/18.
//

#ifndef EMULATE_SINGLE_DATA_TRANSFER_INSTRUCTION_H
#define EMULATE_SINGLE_DATA_TRANSFER_INSTRUCTION_H

#include "../emulate_dir/emulate_main.h"

int execute_instruction_single_data_transfer(struct EmulatorState *,
                                             const struct SingleDataTransferInstruction);

#endif //EMULATE_SINGLE_DATA_TRANSFER_INSTRUCTION_H
