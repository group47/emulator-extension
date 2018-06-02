//
// Created by mhl1817 on 02/06/18.
//

#ifndef SRC_MULTIPLE_LOAD_STORE_H
#define SRC_MULTIPLE_LOAD_STORE_H

#include <stdint.h>
#include <stdbool.h>
#include "../../basic_typedefs.h"
struct MultipleLoadStoreInstruction{
  uint8_t filler     : 4; //1100
  bool loadMemory    : 1;
  RegisterAddress Rb : 3;
  uint8_t RList      : 8;
}__attribute__((packed));

enum ExecutionExitCode execute_instruction_multiple_load_store(const struct MultipleLoadStoreInstruction);

#endif //SRC_MULTIPLE_LOAD_STORE_H
