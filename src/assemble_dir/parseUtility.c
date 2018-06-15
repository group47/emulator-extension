//
// Created by qs4617 on 30/05/18.
//

#include <stdio.h>
#include <assert.h>
#include <memory.h>
#include "symbol_table.h"
#include "tokenizer.h"
#include "utility.h"
#include "parseUtility.h"

struct Instruction parseExpression(char** tokens, int tokenOffset, struct Token* token) {
    switch (token->instructionInfo->instructionType) {
        case DATA_PROCESSING:
            token->operand2 = (uint16_t) getOperand2Immediate(strtolWrapper(*(tokens + tokenOffset)));
            return token->instructionInfo->assemble(token);
        case SINGLE_DATA_TRANSFER:
            token->offset = (uint32_t ) strtolWrapper(*(tokens + tokenOffset));
            return token->instructionInfo->assemble(token);
        default:
            assert(false);
    }
}
struct Instruction parseShiftedRegister(char** tokens, int tokenOffset, struct Token* token) {
    enum ShiftType shiftType = lsl;
    uint16_t shiftedRegister = token->Rm;
    char* shiftname = *(tokens + tokenOffset);
    char* registerOrExpression = *(tokens + tokenOffset + 1);
    if (shiftname[0] != '\0' && shiftname[0] != '\n' && shiftname[0] != ']') {
        // todo: remove those special cases
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

        if (registerOrExpression[0] != '\0') {
            if (registerOrExpression[0] == 'r') {
                shiftedRegister = 0;
                ((struct ImmediateFalseShiftByRegisterTrue *) &shiftedRegister)->filler = 0;
                ((struct ImmediateFalseShiftByRegisterTrue *) &shiftedRegister)->shift_type = shiftType;
                ((struct ImmediateFalseShiftByRegisterTrue *) &shiftedRegister)->Rm = token->Rm;
                ((struct ImmediateFalseShiftByRegisterTrue *) &shiftedRegister)->shift_by_register = true;
                ((struct ImmediateFalseShiftByRegisterTrue *) &shiftedRegister)->Rs =
                        (uint8_t) strtolWrapper(registerOrExpression);
            } else if (strcmp(registerOrExpression, "#") == 0) {
                registerOrExpression = *(tokens + tokenOffset + 2);
                shiftedRegister = 0;
                ((struct ImmediateFalseShiftByRegisterFalse *) &shiftedRegister)->shift_type = shiftType;
                ((struct ImmediateFalseShiftByRegisterFalse *) &shiftedRegister)->Rm = token->Rm;
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