//
// Created by qs4617 on 30/05/18.
//

#ifndef SRC_PARSEDATAPROCESSING_H
#define SRC_PARSEDATAPROCESSING_H

#include "../shared/instructions.h"
#include "tokenizer.h"
struct Instruction assembleDataProcessingInstruction(struct Token*);
struct Instruction parseDataProcessingOperand2(char**, int, struct Token*);
struct Instruction parseDataProcessing1(char **, int, struct Token *);
struct Instruction parseDataProcessing2(char **, int, struct Token *);
struct Instruction parseDataProcessing3(char **, int, struct Token *);
#endif //SRC_PARSEDATAPROCESSING_H
