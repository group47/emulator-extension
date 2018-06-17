//
// Created by francis on 5/27/18.
//

#ifndef EMULATE_DATA_PROCESSING_INSTRUCTION_H
#define EMULATE_DATA_PROCESSING_INSTRUCTION_H

#include "../emulate_dir/emulate_main.h"

int execute_instruction_data_processing(struct EmulatorState *,
                                        struct DataProcessingInstruction);

#endif //EMULATE_DATA_PROCESSING_INSTRUCTION_H
