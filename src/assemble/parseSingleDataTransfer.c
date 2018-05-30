//
// Created by qs4617 on 30/05/18.
//
#include <stdio.h>
#include <memory.h>
#include <assert.h>
#include "extra_data.h"
#include "utility.h"
#include "symbol_table.h"
#include "tokenizer.h"
#include "parseSingleDataTransfer.h"
#include "parseUtility.h"
#include "parseDataProcessing.h"

struct Instruction assembleSingleDataInstruction(struct Token* token) {
    struct SingleDataTransferInstruction binary;
    struct Instruction instruction;
    instruction.type = SINGLE_DATA_TRANSFER;
    binary.cond = token->instructionInfo->condCode;
    binary.filler = 0b01;
    binary.filler2 = 0b00;
    binary.immediateOffset = token->offsetIsImmediate;
    binary.prePostIndexingBit = token->isPreIndexing;
    binary.upBit = !token->offsetIsNegative;
    binary.loadStore = strcmp((char*)token->instructionInfo->mnemonics, "ldr") == 0;
    binary.Rn = token->Rn;
    binary.Rd = token->Rd;
    if(token->use_extra_data){
        assert(token->offset > 0x00ff );
        assert(!binary.immediateOffset);
        binary.Rn = 0b1111;//the program counter
        uint32_t  extra_data_address = 4*add_extra_data(token->offset);
        binary.offset = (uint16_t)(extra_data_address - 4*token->instructionInfo->address - 8);//todo check
    } else{
        binary.offset = (uint16_t)(0x0fff & token->offset);
    }
    instruction.rawInstruction = *(union RawInstruction *)&binary;
    return instruction;
}


// single data transfer syntax 1 : <ldr/str> Rd, <address>
struct Instruction parseSingleDataTransfer1(char **tokens, int tokenOffset, struct Token * token) {
    if (!isRegister(*(tokens + tokenOffset))) {
        fprintf(stderr, "Rd is not a register for single data transfer\n");
        assert(false);
    }
    token->Rd = (uint8_t) strtolWrapper(*(tokens + tokenOffset));
    return parseSingleDataTransferAddress(tokens, tokenOffset + 1, token);
}

// pre-condition
// For data processing only, immediate flag should be true

struct Instruction parseSingleDataTransferAddress(char** tokens, int tokenOffset, struct Token* token) {
    if (strcmp(*(tokens + tokenOffset), "=") == 0) {
        token->isPreIndexing = true;
        token->offsetIsImmediate = false;
        parseExpression(tokens, tokenOffset, token);

        if (token->offset <= 0x00ff && strcmp((char *) (token->instructionInfo->mnemonics), "ldr") == 0) {
            tokens[2][0] = '#';
            token->instructionInfo = &find(token->instructionInfo->symbolTable, "mov")->rawEntry.instructionInfo;
            parseDataProcessing2(tokens, 1, token);
        } else {
            token->use_extra_data = true;
        }
        return token->instructionInfo->assemble(token);
    }

    if (strcmp(*(tokens + tokenOffset), "[") != 0) {
        fprintf(stderr, "address has incorrect format for single data transfer\n");
        assert(false);
    }

    if (!isRegister(*(tokens + tokenOffset + 1))) {
        fprintf(stderr, "Rn is not a register for single data transfer\n");
    }

    token->Rn = (uint8_t) strtolWrapper(*(tokens + tokenOffset + 2));
    if (strcmp(*(tokens + tokenOffset + 3), "]") == 0) {
        if (*(tokens + tokenOffset + 4) == NULL) {
            token->offsetIsImmediate = false;
            token->isPreIndexing = true;
            token->offset = 0;
            return token->instructionInfo->assemble(token);
        }
        token->isPreIndexing = false;
        tokenOffset++;
    } else {
        token->isPreIndexing = true;
    }

    if (strcmp(*(tokens + tokenOffset + 3), "#") == 0) {
        token->offsetIsImmediate = false;
        parseExpression(tokens, tokenOffset + 4, token);
    } else {
        token->offsetIsImmediate = true;
        if (strcmp(*(tokens + tokenOffset + 3), "-") == 0) {
            token->offsetIsNegative = true;
            tokenOffset++;
        } else {
            token->offsetIsNegative = false;
        }
        parseRmShiftedRegister(tokens, tokenOffset + 3, token);
    }
    return token->instructionInfo->assemble(token);
}



