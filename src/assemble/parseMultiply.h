//
// Created by qs4617 on 30/05/18.
//

#ifndef SRC_PARSEMULTIPLY_H
#define SRC_PARSEMULTIPLY_H

#include "../shared/instructions.h"
#include "tokenizer.h"
struct Instruction assembleMultiplyInstruction(struct Token*);
struct Instruction parseMultiply1(char **, int, struct Token *);
struct Instruction parseMultiply2(char **, int, struct Token *);
#endif //SRC_PARSEMULTIPLY_H
