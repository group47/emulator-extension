//
// Created by qs4617 on 30/05/18.
//

#include <stdio.h>
#include <assert.h>
#include <memory.h>
#include "symbol_table.h"
#include "tokenizer.h"
#include "utility.h"
#include "../shared/enums.h"
#include "parseUtility.h"

struct Instruction parseExpression(char** tokens, int tokenOffset, struct Token* token) {
    token->operand2 = getOperand2Immediate(strtolWrapper(*(tokens+tokenOffset)));
    return token->instructionInfo->assemble(token);
}
struct Instruction parseShiftedRegister(char** tokens, int tokenOffset, struct Token* token) {
    enum ShiftType shiftType = lsl;
    uint16_t shiftedRegister = token->Rm;
    char* shiftname = *(tokens + tokenOffset + 1);
    char* registerOrExpression = *(tokens + tokenOffset + 2);
    if (shiftname != NULL && strlen(shiftname) > 0) {
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
                ((struct ImmediateFalseShiftByRegisterTrue *) &shiftedRegister)->shift_by_register = true;
                ((struct ImmediateFalseShiftByRegisterTrue *) &shiftedRegister)->Rs =
                        (uint8_t) strtolWrapper(registerOrExpression);
            } else if (registerOrExpression[0] == '#') {
                ((struct ImmediateFalseShiftByRegisterFalse *) &shiftedRegister)->shift_type = shiftType;
                ((struct ImmediateFalseShiftByRegisterFalse *) &shiftedRegister)->shift_by_register = false;
                ((struct ImmediateFalseShiftByRegisterFalse *) &shiftedRegister)->integer =
                        (uint8_t) strtolWrapper(registerOrExpression);
            } else {
                assert(false);
            }
        }
    }
    token->offset = shiftedRegister;
    token->operand2 = shiftedRegister;

    return token->instructionInfo->assemble(token);
}

struct Instruction parseRmShiftedRegister(char** tokens, int tokenOffset, struct Token* token) {
    if (!isRegister(*(tokens + tokenOffset))) {
        fprintf (stderr, "operand2 for data processing has incorrect format\n");
    }
    token->Rm = (uint8_t)strtolWrapper(*(tokens + tokenOffset));

    return parseShiftedRegister(tokens, tokenOffset + 1, token);
}