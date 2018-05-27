//
// Created by fpn17 on 27/05/18.
//


#include <stdint.h>
#include <glob.h>
#include <stdlib.h>
#include "emulate_main.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
    DoSomethingInterestingWithMyAPI(Data, Size);
    struct EmulatorState *state = malloc(sizeof(struct EmulatorState));
    emulate(state,Data,Size);
    return 0;  // Non-zero return values are reserved for future use.
}
