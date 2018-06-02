//
// Created by mhl1817 on 02/06/18.
//

#ifndef SRC_LOAD_STORE_WITH_IMMEDIATE_OFFSET_H
#define SRC_LOAD_STORE_WITH_IMMEDIATE_OFFSET_H

#include <stdbool.h>
#include "../../basic_typedefs.h"
#include "../../util/common_enums.h"

struct LoadStoreWithImmediateOffsetInstruction {
  uint8_t filler     : 3; //011
  bool byteTransfer  : 1;
  bool loadMemory    : 1;
  uint8_t offset     : 5;
  RegisterAddress Rb : 3;
  RegisterAddress Rd : 3;
}__attribute__((packed));

enum ExecutionExitCode execute_instruction_load_store_with_immeditate_offset(const struct LoadStoreWithImmediateOffsetInstruction);


#endif //SRC_LOAD_STORE_WITH_IMMEDIATE_OFFSET_H
