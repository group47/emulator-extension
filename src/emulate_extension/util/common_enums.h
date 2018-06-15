//
// Created by francis on 6/2/18.
//

#ifndef SRC_COMMON_ENUMS_H
#define SRC_COMMON_ENUMS_H

enum Cond {
    eq = 0b0000,
    ne = 0b0001,
    cs = 0b0010,
    cc = 0b0011,
    mi = 0b0100,
    pl = 0b0101,
    vs = 0b0110,
    vc = 0b0111,
    hi = 0b1000,
    ls = 0b1001,
    ge = 0b1010,
    lt = 0b1011,
    gt = 0b1100,
    le = 0b1101,
    al = 0b1110
    //never = 0b1111 -> software interrupt
};
enum ExecutionExitCode {
    BRANCH = -2, TERMINATE = -1, DIDNT_EXECUTE = 0, OK = 1
};

enum LoadStore {
    LOAD = 0b1, STORE = 0b0
};

enum PrePostIndexing {
    PRE = 0b1, POST = 0b0
};

#endif //SRC_COMMON_ENUMS_H
