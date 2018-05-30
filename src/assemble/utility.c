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

long strtolWrapper(char* str) {
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

uint32_t getShiftedRegister(char* shiftname, char* registerOrExpression, uint8_t Rm) {
    enum ShiftType shiftType = lsl;
    uint16_t shiftedRegister = 0;
    if (shiftname != NULL) {
        if (strcmp(shiftname, "lsl") == 0) {
            shiftType = lsl;
        } else if (strcmp(shiftname, "lsr") == 0) {
            shiftType = lsr;
        } else if (strcmp(shiftname, "asr") == 0) {
            shiftType = asr;
        } else if (strcmp(shiftname, "ror") == 0) {
            shiftType = ror;
        } else {
            assert(false);
        }

        if (registerOrExpression != NULL) {
            if (registerOrExpression[0] == 'r') {
                ((struct ImmediateFalseShiftByRegisterTrue *) &shiftedRegister)->filler = 0;
                ((struct ImmediateFalseShiftByRegisterTrue *) &shiftedRegister)->shift_type = shiftType;
                ((struct ImmediateFalseShiftByRegisterTrue *) &shiftedRegister)->Rm = Rm;
                ((struct ImmediateFalseShiftByRegisterTrue *) &shiftedRegister)->shift_by_register = true;
                ((struct ImmediateFalseShiftByRegisterTrue *) &shiftedRegister)->Rs =
                        (uint8_t) strtolWrapper(registerOrExpression);
            } else if (registerOrExpression[0] == '#') {
                ((struct ImmediateFalseShiftByRegisterFalse *) &shiftedRegister)->shift_type = shiftType;
                ((struct ImmediateFalseShiftByRegisterFalse *) &shiftedRegister)->Rm = Rm;
                ((struct ImmediateFalseShiftByRegisterFalse *) &shiftedRegister)->shift_by_register = false;
                ((struct ImmediateFalseShiftByRegisterFalse *) &shiftedRegister)->integer =
                        (uint8_t) strtolWrapper(registerOrExpression);
            } else {
                assert(false);
            }
        }
    } else {
        shiftedRegister = Rm;
    }
    return shiftedRegister;
}

// pre-condition
// For data processing only, immediate flag should be true
long assembleExpressionOrShiftedRegister(bool* immediateFlag, char* registerOrExpression, char* shiftname, char* shiftedRegisterOrExpression) {
    uint32_t result;
    if (registerOrExpression[0] == '#') {
        result = getOperand2Immediate(strtolWrapper(registerOrExpression));
    } else {
        *immediateFlag = !(*immediateFlag);
        result = (uint16_t) getShiftedRegister(shiftname, shiftedRegisterOrExpression, (uint8_t)strtolWrapper(registerOrExpression));
    }
    return result;
}
