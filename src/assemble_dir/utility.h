//
// Created by qs4617 on 29/05/18.
//

#ifndef SRC_UTILITY_H
#define SRC_UTILITY_H

#include <stdint.h>
#include <stdbool.h>

long strtolWrapper(char *);

uint16_t getOperand2Immediate(long);

bool isNegative(char *);

bool secondToLastCharIs(const char *, char);

bool isRegister(char *);

#endif //SRC_UTILITY_H
