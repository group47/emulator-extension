//
// Created by qs4617 on 03/06/18.
//

#ifndef SRC_PSRTRANSFER_H
#define SRC_PSRTRANSFER_H


#include <stdint.h>
#include <stdbool.h>
#include "../../util/common_enums.h"
#include "../../basic_typedefs.h"

struct TransferPSRContentsToRegister {
    uint16_t filler0000_0000_0000_position11 : 12;
    RegisterAddress Rd : 4;
    uint8_t filler001111_position21 : 6;
    bool sourcePSR : 1;
    uint8_t filler00010_position27: 5;
    enum Cond cond : 4;
}__attribute__((packed));

struct TransferRegisterContentsToPSR {
    RegisterAddress Rm : 4;
    uint32_t filler1010_0111_1100_0000_00_position_21 : 18;
    bool destinationPSR : 1;
    uint8_t filler00010_position27 : 5;
    enum Cond cond : 4;
}__attribute__((packed));

struct TransferRegisterContentsOrImmediateValueToPSRFlag {
    uint16_t sourceOperand : 12;
    uint16_t filler1010_0011_11_position21 : 10;
    bool destinationPSR : 1;
    uint8_t filler10_position24 : 2;
    bool immediateOperand : 1;
    uint8_t filler00_position27 : 2;
    enum Cond cond : 4;
}__attribute__((packed));

enum ExecutionExitCode execute_instruction_transfer_psr_contents_to_register(struct TransferPSRContentsToRegister);

enum ExecutionExitCode execute_instruction_transfer_register_contents_to_psr(struct TransferRegisterContentsToPSR);

enum ExecutionExitCode execute_instruction_transfer_register_contents_or_immediate_value_to_psrflag(
        struct TransferRegisterContentsOrImmediateValueToPSRFlag);


#endif //SRC_PSRTRANSFER_H
