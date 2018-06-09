//
// Created by qs4617 on 02/06/18.
//

#ifndef SRC_COPROCESSOR_DATA_OPERATIONS_H
#define SRC_COPROCESSOR_DATA_OPERATIONS_H

#include <stdint.h>
#include "../../basic_typedefs.h"
#include "../../util/common_enums.h"

struct CoprocessorDataOperationsInstruction {
    RegisterAddress CoOperandRegister_position3 : 4; // Coprocessor operand register
    uint8_t filler0_position4 : 1;
    RegisterAddress CoInformation :3; // Coprocessor information
    RegisterAddress CoNumber : 4; // Coprocessor number
    RegisterAddress CoDestinationRegister : 4; // Coprocessor destination register
    RegisterAddress CoOperandRegister_position19 : 4; // Coprocessor operand register
    RegisterAddress CoOperationCode : 4; // Coprocessor operation code
    uint8_t filler1110_position27 : 4;
    enum Cond cond : 4;
}__attribute__((packed));


enum ExecutionExitCode execute_instruction_coprocessor_data_operations(struct CoprocessorDataOperationsInstruction);

#endif //SRC_COPROCESSOR_DATA_OPERATIONS_H
