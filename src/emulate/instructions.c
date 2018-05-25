//
// Created by francis on 5/23/18.
//

#include <stdbool.h>
#include "emulate_main.h"

bool is_arithmetic(enum OpCode opCode) {
  return opCode == add || opCode == sub || opCode == rsb || opCode == cmp;
}
bool is_logical(enum OpCode opCode) {
  return !is_arithmetic(opCode);
}

