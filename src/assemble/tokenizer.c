//
// Created by ryro on 2018/5/26.
//

#include <string.h>
#include <stdlib.h>

#define MAX_TOKENS = 32

// Might need to modify based on further included cases
// This will definitely break with register cases
// I didn't extract the register number or the immediate value from the string
// Might need to distinguish them later

char** tokenizer(char* instruction) {
    char* tokensFirstPass[MAX_TOKENS];
    char* tokensSecondPass[MAX_TOKENS];

    char* token1;
    char* token2;

    token1 = strtok(instruction, ",");

    int countFirstPass = 0;

    while (token1 != NULL) {
        tokensFirstPass[countFirstPass] = malloc(511);
        memcpy(tokensFirstPass[countFirstPass], token1, strlen(token1));
        token1 = strtok(NULL, ",");
        countFirstPass++;
    }

    int countSecondPass = 0;

    for (int i = 0; i < countFirstPass; i++) {
        token2 = strtok(tokensFirstPass[i], " ");
        while (token2 != NULL) {
            tokensSecondPass[countSecondPass] = malloc(511);
            memcpy(tokensSecondPass[countSecondPass], token2, strlen(token2));
            countSecondPass++;
        }
    }

    return tokensSecondPass;
}
