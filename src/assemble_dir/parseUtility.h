//
// Created by qs4617 on 30/05/18.
//

#ifndef SRC_PARSEUTILITY_H
#define SRC_PARSEUTILITY_H

#include "../shared/instructions.h"
#include "tokenizer.h"
struct Instruction parseExpression(char**, int, struct Token*);
struct Instruction parseShiftedRegister(char**, int, struct Token*);
struct Instruction parseRmShiftedRegister(char**, int, struct Token*);
#endif //SRC_PARSEUTILITY_H
