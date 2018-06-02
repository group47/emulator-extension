//
// Created by francis on 6/2/18.
//

#ifndef SRC_COMMON_ENUMS_H
#define SRC_COMMON_ENUMS_H

enum Cond {
  eq = 0b0000,
  ne = 0b0001,
  ge = 0b1010,
  lt = 0b1011,
  gt = 0b1100,
  le = 0b1101,
  al = 0b1110
};
enum ExecutionExitCode{
  BRANCH = -2,TERMINATE = -1,DIDNT_EXECUTE = 0, OK = 1
};

enum LoadStore{
    LOAD = 0b1,STORE = 0b0
};

enum PrePostIndexing{
    PRE = 0b1,POST = 0b0
};

#endif //SRC_COMMON_ENUMS_H
