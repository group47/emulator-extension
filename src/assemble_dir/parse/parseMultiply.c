//
// Created by qs4617 on 30/05/18.
//

// multiply syntax 1 : mul Rd, Rm, Rs

#include <memory.h>
#include <assert.h>
#include <stdio.h>
#include "../../shared/instructions.h"
#include "../symbol_table.h"
#include "../utility.h"
#include "../tokenizer.h"

struct Instruction assembleMultiplyInstruction(struct Token* token) {
    struct MultiplyInstruction binary;
    struct Instruction instruction;
    instruction.type = MULTIPLY;
    binary.cond = token->instructionInfo->condCode;
    binary.filler = 0b000000;
    binary.accumulate =
      strcmp((char*)token->instructionInfo->mnemonics, "mla") == 0;
    binary.destinationRegister = token->Rd;
    binary.Rn = token->Rn;
    binary.Rs = token->Rs;
    binary.filler2 = 0b1001;
    binary.Rm = token->Rm;
    binary.setConditionCodes = 0b0;
    instruction.rawInstruction = *(union RawInstruction *)&binary;
    return instruction;
}

struct Instruction parseMultiply1(char **tokens, int tokenOffset, struct Token * token) {

    if (!(isRegister(*(tokens + tokenOffset)))) {
        fprintf(stderr, "Rd is not a register for data processing");
        assert(false);
    }

    if (!(isRegister(*(tokens + tokenOffset + 1)))) {
        fprintf(stderr, "Rm is not a register for data processing");
        assert(false);
    }

    if (!(isRegister(*(tokens + tokenOffset + 2)))) {
        fprintf(stderr, "Rs is not a register for data processing");
        assert(false);
    }

    token->Rd = (uint8_t)strtolWrapper(*(tokens + tokenOffset));
    token->Rm = (uint8_t)strtolWrapper(*(tokens + tokenOffset + 1));
    token->Rs = (uint8_t)strtolWrapper(*(tokens + tokenOffset + 2));
    return token->instructionInfo->assemble(token);
}

// multiply syntax 2 : mla Rd, Rm, Rs, Rn
struct Instruction parseMultiply2(char **tokens, int tokenOffset, struct Token *token) {

    if (!(isRegister(*(tokens + tokenOffset)))) {
        fprintf(stderr, "Rd is not a register for data processing");
        assert(false);
    }

    if (!(isRegister(*(tokens + tokenOffset + 1)))) {
        fprintf(stderr, "Rm is not a register for data processing");
        assert(false);
    }

    if (!(isRegister(*(tokens + tokenOffset + 2)))) {
        fprintf(stderr, "Rs is not a register for data processing");
        assert(false);
    }

    if (!(isRegister(*(tokens + tokenOffset + 3)))) {
        fprintf(stderr, "Rn is not a register for data processing");
        assert(false);
    }

    token->Rd = (uint8_t)strtolWrapper(*(tokens + tokenOffset));
    token->Rm = (uint8_t)strtolWrapper(*(tokens + tokenOffset + 1));
    token->Rs = (uint8_t)strtolWrapper(*(tokens + tokenOffset + 2));
    token->Rn = (uint8_t)strtolWrapper(*(tokens + tokenOffset + 3));
    return token->instructionInfo->assemble(token);
}
