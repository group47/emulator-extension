//
// Created by qs4617 on 03/06/18.
//

#ifndef SRC_EXCEPTION_H
#define SRC_EXCEPTION_H


#include <stdbool.h>
#include "emulator_state.h"

bool has_exceptions();

bool has_exceptions_prev(struct CPUState *state);

void handle_exception();

#endif //SRC_EXCEPTION_H
