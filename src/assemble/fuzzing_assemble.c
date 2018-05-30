//
// Created by francis on 5/30/18.
//

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "assemble.h"

int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
//   DoSomethingInterestingWithMyAPI(Data, Size);
//  struct EmulatorState *state = malloc(sizeof(struct EmulatorState));
//  emulate(state,Data,Size);
  FILE *fp = fopen("/tmp/test","w+");

  fwrite(Data,Size,1,fp);
  fclose(fp);

  char* arr[3] = {"","/tmp/test","/temp/out"};

  main2(3,arr);

  return 0;  // Non-zero return values are reserved for future use.
}
