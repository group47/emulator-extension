//
// Created by qs4617 on 30/05/18.
//

#ifndef SRC_PARSESINGLEDATATRANSFER_H
#define SRC_PARSESINGLEDATATRANSFER_H


#include "../../shared/instructions.h"
#include "../tokenizer.h"

struct Instruction assembleSingleDataInstruction(struct Token*);
struct Instruction parseSingleDataTransferAddress(char**, int, struct Token*);
struct Instruction parseSingleDataTransfer1(char **, int, struct Token *);
#endif //SRC_PARSESINGLEDATATRANSFER_H
