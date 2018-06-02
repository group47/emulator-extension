//
// Created by mhl1817 on 02/06/18.
//

#ifndef SRC_SP_RELATIVE_LOAD_STORE_H
#define SRC_SP_RELATIVE_LOAD_STORE_H

#include <stdbool.h>
#include <stdint.h>
#include "../../util/common_enums.h"
#include "../../basic_typedefs.h"

struct SPRelativeLoadStoreInstruction {
  uint8_t filler     : 4; //1001
  bool loadMemory    : 1;
  RegisterAddress Rd : 3;
  uint8_t word       : 8;
}__attribute__((packed));

enum ExecutionExitCode execute_instruction_SP_relative_load_store(const struct SPRelativeLoadStoreInstruction);


#endif //SRC_SP_RELATIVE_LOAD_STORE_H
