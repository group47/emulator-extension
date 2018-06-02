//
// Created by qs4617 on 02/06/18.
//

#ifndef SRC_COPROCESSOR_DATA_TRANSFERS_H
#define SRC_COPROCESSOR_DATA_TRANSFERS_H

#include <stdint.h>
#include <stdbool.h>
#include "../../../shared/enums.h"
#include "../../util/common_enums.h"
#include "../../basic_typedefs.h"

struct CoprocessorDataTransfersInstruction {
    uint8_t offset : 8;
    RegisterAddress CoNumber : 4;
    RegisterAddress CoSourceDestinationRegister : 4;
    RegisterAddress baseRegister : 4;
    enum LoadStore loadStoreBit : 1;
    bool writeBackBit : 1;
    bool transferLength : 1;
    bool upDownBit : 1;
    bool prePostIndexingBit : 1;
    uint8_t filler110_position27 : 3;
    enum Cond cond : 4;
}__attribute__((packed));

enum ExecutionExitCode execute_instruction_coprocessor_data_transfers(struct CoprocessorDataTransfersInstruction);

#endif //SRC_COPROCESSOR_DATA_TRANSFERS_H
