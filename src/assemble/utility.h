//
// Created by qs4617 on 29/05/18.
//

#ifndef SRC_UTILITY_H
#define SRC_UTILITY_H

#include <stdint.h>
#include <stdbool.h>

long strtolWrapper(char* str);
uint16_t getOperand2Immediate(long operand2Val);
bool isNegative(char* number);
bool secondToLastCharIs(const char *target, char c);



// Specific function for assembling overlapping section between instruction
uint32_t getShiftedRegister(char*, char*, uint8_t);
long parseDataProcessingOperand2(bool *, char *, char *, char *);
bool isRegister(char* token);


#endif //SRC_UTILITY_H
