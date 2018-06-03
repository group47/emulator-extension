//
// Created by mhl1817 on 02/06/18.
//

#ifndef SRC_LOAD_ADDRESS_H
#define SRC_LOAD_ADDRESS_H

#include <stdbool.h>
#include "../../basic_typedefs.h"
#include "../../util/common_enums.h"

struct LoadAddressInstruction {
  uint8_t filler1010     : 4; //1010
  bool stackPointer  : 1;
  RegisterAddress Rd : 3;
  uint8_t word       : 8;
}__attribute__((packed));

enum ExecutionExitCode execute_instruction_load_address(const struct LoadAddressInstruction);

#endif //SRC_LOAD_ADDRESS_H
