//
// Created by qs4617 on 30/05/18.
//

#ifndef SRC_PARSEBRANCH_H
#define SRC_PARSEBRANCH_H

#include "../shared/instructions.h"
#include "tokenizer.h"
struct Instruction assembleBranchInstruction(struct Token*);
struct Instruction parseBranch1(char **, int, struct Token *);

#endif //SRC_PARSEBRANCH_H
