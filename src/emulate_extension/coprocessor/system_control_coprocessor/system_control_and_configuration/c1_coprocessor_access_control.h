//
// Created by qs4617 on 07/06/18.
//

#ifndef SRC_C1_COPROCESSOR_ACCESS_CONTROL_H
#define SRC_C1_COPROCESSOR_ACCESS_CONTROL_H

#include <stdint.h>
#include "../../../instructions/arm/coprocessor_data_transfers.h"

struct C1_coprocessor_access_control_register {
   uint8_t cp0 : 2;
   uint8_t cp1 : 2;
   uint8_t cp2 : 2;
   uint8_t cp3 : 2;
   uint8_t cp4 : 2;
   uint8_t cp5 : 2;
   uint8_t cp6 : 2;
   uint8_t cp7 : 2;
   uint8_t cp8 : 2;
   uint8_t cp9 : 2;
   uint8_t cp10: 2;
   uint8_t cp11: 2;
   uint8_t cp12: 2;
   uint8_t cp13: 2;
   uint8_t sbz_unp : 4;
}__attribute__((packed));

enum ExecutionExitCode execute_coprocessor_access_control(struct CoprocessorDataTransfersInstruction);

#endif //SRC_C1_COPROCESSOR_ACCESS_CONTROL_H
