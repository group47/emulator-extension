//
// Created by qs4617 on 30/05/18.
//


#include <memory.h>
#include "../symbol_table.h"
#include "../tokenizer.h"
#include "parseDataProcessing.h"

// for lsl
struct Instruction parseSpecial1(char **tokens, int tokenOffset, struct Token *token) {


    char *op = calloc(20, sizeof(char));
    char *Rn1 = calloc(20, sizeof(char));
    char *Rn2 = calloc(20, sizeof(char));
    char *shiftname = calloc(20, sizeof(char));
    char *sharp = calloc(20, sizeof(char));
    char *expr = calloc(20, sizeof(char));
    memcpy(op, "mov", 4);
    memcpy(Rn1, tokens[1], strlen(tokens[1]) + 1);
    memcpy(Rn2, tokens[1], strlen(tokens[1]) + 1);
    memcpy(shiftname, "lsl", 4);
    memcpy(sharp, "#", 2);
    memcpy(expr, tokens[3], strlen(tokens[3]) + 1);

    for (int i = 0; i < 6; i++) {
        free(tokens[i]);
    }

    tokens[0] = op;
    tokens[1] = Rn1;
    tokens[2] = Rn2;
    tokens[3] = shiftname;
    tokens[4] = sharp;
    tokens[5] = expr;

    /*
    char* Rn = tokens[1];
    char* v1 = tokens[2];
    char* v2 = tokens[3];
    char* v3 = tokens[4];
    for (int i = 4; i < 7; i++) {
        //if (tokens[i] == NULL) {
            tokens[i] = malloc(sizeof(char) * 500);
        //}
    }
    memcpy(tokens[0], "mov", 4);
    tokens[1] = Rn;
    tokens[2] = Rn;
    tokens[4] = v1;
    tokens[5] = v2;
    tokens[6] = v3;
    memcpy(tokens[3], "lsl", 4);
     */

/*
    char** tokensRestructure = malloc(sizeof(char*)*20);
    for (int i = 0; i < 7; i++) {
        tokensRestructure[i] = malloc(sizeof(char)*10);
    }
    memcpy(tokensRestructure[0], "mov", 4);
    tokensRestructure[1] = tokens[1];
    tokensRestructure[2] = tokens[1];
    memcpy(tokensRestructure[3], "lsl", 4);
    tokensRestructure[4] = tokens[2];
    tokensRestructure[5] = tokens[3];
    tokensRestructure[6] = tokens[4];
*/

    initializeToken(token);

    token->instructionInfo = &find(token->instructionInfo->symbolTable, "mov")->rawEntry.instructionInfo;

    return parseDataProcessing2(tokens, 1, token);//todo
}
