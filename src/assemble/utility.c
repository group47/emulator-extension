//
// Created by qs4617 on 29/05/18.
//

#include <ctype.h>
#include <assert.h>
#include <lzma.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <x86intrin.h>
#include "../shared/enums.h"
#include "../shared/instructions.h"
#include "tokenizer.h"
#include "assemble.h"

long strtolWrapper(char* str) {
    fprintf(stderr, "%s", str);
    while (!isdigit(*str)) {
        assert(*str != '\0');
        str++;
    }
    long result;
    if (strstr(str, "0x")) {
        result = strtol(str, NULL, 16);
    } else {
        result = strtol(str, NULL, 10);
    }
    return result;
}

uint16_t getOperand2Immediate(long operand2Val) {
    bool found = false;
    uint32_t result = (uint32_t)operand2Val;
    uint32_t count;
    for (count = 0; count < 16; ++count) {
        if ((0x000000ff & result) == result) {
            found = true;
            break;
        }
        result = __rold(result, 2);
    }
    assert(found);
    result |= count << 8;
    return (uint16_t) result;

}

bool isNegative(char* number) {
    for (int i = 0; i < 3; i++) {
        if (number[i] == '-') {
            return true;
        }
        if (number[i] == '\0') {
            return false;
        }
    }
    return false;
}

bool secondToLastCharIs(const char *target, char c) {
    return target[strlen(target) - 2] == c;
}

// post-condition: true for formats as 'r0' and '-r0'
bool isRegister(char* token) {
    return token[0] == 'r' || token[1] == 'r';
}






