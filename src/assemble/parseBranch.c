//
// Created by qs4617 on 30/05/18.
//

#include <assert.h>
#include <memory.h>
#include "tokenizer.h"
#include "parseBranch.h"
#include "../shared/branch_instruction.h"
#include "symbol_table.h"

struct Instruction assembleBranchInstruction(struct Token* token) {
    struct BranchInstruction binary;
    struct Instruction instruction;
    instruction.type = BRANCH_INSTRUCTION;
    binary.offset = token->offset;
    binary.cond = token->instructionInfo->condCode;
    binary.filler1 = 0b0;
    binary.filler2 = 0b101;
    instruction.rawInstruction = *(union RawInstruction *)&binary;
    return instruction;
}
struct Instruction parseBranch1(char **tokens, int tokenOffset, struct Token * token) {
    assert(token->instructionInfo->instructionType == BRANCH_INSTRUCTION);
    assert(token->instructionInfo != NULL);
    // todo: figure out how to combine labelling process with tokenization
    char* label= tokens[1];
    //remove newline:
    label[strlen(label) - 1] = '\0';
    struct Entry* entry = find(token->instructionInfo->labelAddress,label);
    if(entry == NULL){
        //must be in first pass, and this value is unused
        struct Instruction badVal;
        badVal.type = BRANCH_INSTRUCTION_INVALID;
        return badVal;
    }
    assert(entry->entryType ==  LABEL);
    const uint32_t  target_address = entry->rawEntry.label.address;
    const int32_t offset = (target_address - token->instructionInfo->address - 2);
    token->offset= offset;
    return token->instructionInfo->assemble(token);
}
