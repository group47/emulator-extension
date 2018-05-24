#include <stdlib.h>

#include "emulate/emulate_main.h"

int main(int argc, char **argv) {
  if(argc != 2){
    fprintf(stderr,
            "the end of the world has come, or you entered the wrong number of arguments");
    return -100000;
  }
  printf("%s\n", argv[1]);
  const char *filename = argv[1];
  int fileDescriptor = open(filename, O_RDONLY);
  if (fileDescriptor == -1) {
    fprintf(stderr,
            "the end of the world has come, or you entered the wrong filename");
    return -100000;
  }

  uint32_t *rawData = (uint32_t *) malloc(sizeof(uint32_t[MAX_INSTRUCTION_INPUT_FILE_SIZE]));
  size_t amountRead = sizeof(byte) * read(fileDescriptor,rawData,sizeof(uint32_t[MAX_INSTRUCTION_INPUT_FILE_SIZE]));
  assert(amountRead % sizeof(uint32_t) == 0);
  struct EmulatorState* emulatorState = malloc(sizeof(struct EmulatorState));
  memset(rawData,0, sizeof(struct EmulatorState));
  emulate(emulatorState,
          rawData,
          (unsigned int) (amountRead / sizeof(uint32_t)));
  close(fileDescriptor);
  free(emulatorState);
  free(rawData);
}
