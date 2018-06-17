//
// Created by qs4617 on 29/05/18.
//

#include <ctype.h>
#include <lzma.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <x86intrin.h>

long strtolWrapper(char *str) {
    while (!isdigit(*str)) {
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
    uint32_t result = (uint32_t) operand2Val;
    uint32_t count;
    for (count = 0; count < 16; ++count) {
        if ((0x000000ff & result) == result) {
            break;
        }
        result = __rold(result, 2);
    }
    result |= count << 8;
    return (uint16_t) result;

}

bool isNegative(char *number) {
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
    if (strlen(target) < 2)
        return false;
    return target[strlen(target) - 2] == c;
}

// post-condition: true for formats as 'r0' and '-r0'
bool isRegister(char *token) {
    return token[0] == 'r' || token[1] == 'r';
}






