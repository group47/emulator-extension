//
// Created by qs4617 on 30/05/18.
//

#include <assert.h>
#include <memory.h>
#include <stdio.h>
#include "../shared/enums.h"
#include "../shared/instructions.h"
#include "symbol_table.h"
#include "tokenizer.h"
#include "parseDataProcessing.h"
#include "utility.h"
#include "parseUtility.h"

struct Instruction assembleDataProcessingInstruction(struct Token* token) {
    struct DataProcessingInstruction binary;
    struct Instruction instruction;
    binary.cond = token->instructionInfo->condCode;
    binary.filler = 0b00;
    binary.opcode = token->instructionInfo->opCode;
    binary.immediateOperand = token->operand2IsImmediate;
    binary.setConditionCodes =
            token->instructionInfo->opCode == tst
            || token->instructionInfo->opCode == teq
            || token->instructionInfo->opCode == cmp;
    binary.Rn = token->Rn;
    binary.Rd = token->Rd;
    binary.secondOperand = (uint16_t) token->operand2;
    instruction.rawInstruction =  *(union RawInstruction *)&binary;
    instruction.type = DATA_PROCESSING;
    return instruction;
}
struct Instruction parseDataProcessingOperand2(char** tokens, int tokenOffset, struct Token* token) {
    if (strcmp(*(tokens + tokenOffset), "#") == 0) {
        token->operand2IsImmediate = true;
        return parseExpression(tokens, tokenOffset + 1, token);
    }
    token->operand2IsImmediate = false;
    return parseRmShiftedRegister(tokens, tokenOffset, token);

}
//data processing syntax1 :<opcode> Rd, Rn, <Operand2>
struct Instruction parseDataProcessing1(char **tokens, int tokenOffset, struct Token * token) {

    if (!(isRegister(*(tokens + tokenOffset)))) {
        fprintf(stderr, "Rd is not a register for data processing");
        assert(false);
    }

    if (!(isRegister(*(tokens + tokenOffset + 1)))) {
        fprintf(stderr, "Rn is not a register for data processing");
        assert(false);
    }

    token->Rd = (uint8_t)strtolWrapper(*(tokens + tokenOffset));
    token->Rn = (uint8_t)strtolWrapper(*(tokens + tokenOffset + 1));
    return parseDataProcessingOperand2(tokens, tokenOffset + 2, token);
}

//data processing syntax 2 : mov Rd, <Operand2>
struct Instruction parseDataProcessing2(char **tokens, int tokenOffset, struct Token * token) {

    if (!(isRegister(*(tokens + tokenOffset)))) {
        fprintf(stderr, "Rd is not a register for data processing");
        assert(false);
    }

    token->Rd = (uint8_t)strtolWrapper(*(tokens + tokenOffset));
    return parseDataProcessingOperand2(tokens, tokenOffset + 1, token);
}

//data processing syntax 3: <opcode> Rn, <Operand2>
struct Instruction parseDataProcessing3(char **tokens, int tokenOffset, struct Token * token) {

    if (!(isRegister(*(tokens + tokenOffset)))) {
        fprintf(stderr, "Rn is not a register for data processing");
        assert(false);
    }

    token->Rn = (uint8_t) strtolWrapper(*(tokens + tokenOffset));
    return parseDataProcessingOperand2(tokens, tokenOffset + 1, token);
}

