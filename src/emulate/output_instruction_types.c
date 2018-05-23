//
// Created by francis on 5/24/18.
//

#include <assert.h>
#include <stdio.h>
#include <stdint-gcc.h>
#include <stdlib.h>
#include <zconf.h>
#include <fcntl.h>
#include "output_instruction_types.h"
#include "emulate_main.h"
#include "instructions.h"

int main(int argc , const char *argv[]){
    assert(sizeof(struct DataProcessingInstruction) == sizeof(int32_t));
    assert(sizeof(struct BranchInstruction) == sizeof(int32_t));
    assert(sizeof(struct MultiplyInstruction) == sizeof(int32_t));
    assert(sizeof(struct SingleDataTransferInstruction) == sizeof(int32_t));

    assert(argc == 2);
    printf("%s\n",argv[1]);
    const char * filename = argv[1];
    int fileDescriptor = open(filename,O_RDONLY);
    if(fileDescriptor == -1){
        fprintf(stderr,"the end of the world has come, or you entered the wrong filename");
        return -100000;
    }

    int32_t* rawData = (int32_t*) malloc(sizeof(int32_t[1000]));
    //todo magic nnumber, todo what if theres more
    int amountRead = sizeof(byte)*read(fileDescriptor, rawData, sizeof(int32_t[1000]));// todo warning
    assert(amountRead % sizeof(int32_t) == 0);
    emulate(malloc(sizeof(struct EmulatorState)),rawData,amountRead/ sizeof(int32_t));
    close(fileDescriptor);
}