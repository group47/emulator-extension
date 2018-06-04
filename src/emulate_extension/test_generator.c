//
// Created by fpn17 on 03/06/18.
//

#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include "test_generator.h"
#include "instructions/arm/arm_instruction.h"
#include "util/static_asserts.h"
#include <limits.h>
#include <time.h>


//enum ArmInstructionType{
//    ARM_BLOCK_DATA_TRANSFER = 0,
//    ARM_BRANCH = 1,
//    ARM_BRANCH_AND_EXCHANGE = 2,
//    ARM_COPROCESSOR_DATA_OPERATIONS = 3,
//    ARM_COPROCESSOR_DATA_TRANSFER = 4,
//    ARM_COPROCESSOR_REGISTER_TRANSFER = 5,
//    ARM_DATA_PROCESSING = 6,
//    ARM_HALFWORD_AND_SIGNED_DATA_TRANSFER_REGISTER_OFFSET = 7,
//    ARM_HALFWORD_AND_SIGNED_DATA_TRANSFER_IMMEDIATE_OFFSET= 8,
//    ARM_MULIPLY = 9,
//    ARM_MULTIPLY_LONG = 10,
//    ARM_SINGLE_DATA_SWAP = 11,
//    ARM_SINGLE_DATA_TRANSFER = 12,
//    ARM_SOFTWARE_INTERRUPT = 13,
//    ARM_UNDEFINED = 14,
//};

static const char *type_to_string[15] = {"ARM_BLOCK_DATA_TRANSFER",
                                         "ARM_BRANCH",
                                         "ARM_BRANCH_AND_EXCHANGE",
                                         "ARM_COPROCESSOR_DATA_OPERATIONS",
                                         "ARM_COPROCESSOR_DATA_TRANSFER",
                                         "ARM_COPROCESSOR_REGISTER_TRANSFER",
                                         "ARM_DATA_PROCESSING",
                                         "ARM_HALFWORD_AND_SIGNED_DATA_TRANSFER_REGISTER_OFFSET",
                                         "ARM_HALFWORD_AND_SIGNED_DATA_TRANSFER_IMMEDIATE_OFFSET",
                                         "ARM_MULTIPLY",
                                         "ARM_MULTIPLY_LONG",
                                         "ARM_SINGLE_DATA_SWAP",
                                         "ARM_SINGLE_DATA_TRANSFER",
                                         "ARM_SOFTWARE_INTERRUPT",
                                         "ARM_UNDEFINED"};
static const uint32_t filler_mask[15] = {
        0b00001110000000000000000000000000,//block transfer
        0b00001110000000000000000000000000,//branch
        0b00001111111111111111111111110000,//branch and exchange
        0b00001111000000000000000000010000,//coprocessor data operation
        0b00001110000000000000000000000000,//coprocessor data transfer
        0b00001111000000000000000000010000,//coprocessor register transfer
        0b00001100000000000000000000000000,//data processing
        0b00001110010000000000111110010000,//halfword and signed data transfer w/ register offset
        0b00001110010000000000000010010000,//halfword and signed data transfer w/ immediate offset
        0b00001111110000000000000011110000,//multiply
        0b00001111100000000000000011110000,//multiply long
        0b00001111101100000000111111110000,//single data swap
        0b00001100000000000000000000000000,//single data transfer
        0b00001111000000000000000000000000,//software interrupt
        0b00001110000000000000000000010000,//undefined
};

static const uint32_t filler_expected_values[15] = {
        0b00001000000000000000000000000000,//block transfer
        0b00001010000000000000000000000000,//branch
        0b00000001001011111111111100010000,//branch and exchange
        0b00001110000000000000000000000000,//coprocessor data operation
        0b00001100000000000000000000000000,//coprocessor data transfer
        0b00001110000000000000000000010000,//coprocessor register transfer
        0b00000000000000000000000000000000,//data processing
        0b00000000000000000000000010010000,//halfword and signed data transfer w/ register offset
        0b00000000010000000000000010010000,//halfword and signed data transfer w/ immediate offset
        0b00000000000000000000000010010000,//multiply
        0b00000000100000000000000010010000,//multiply long
        0b00000001000000000000000010010000,//single data swap
        0b00000100000000000000000000000000,//single data transfer
        0b00001111000000000000000000000000,//software interrupt
        0b00000110000000000000000000010000,//undefined
};


static const char *output_file;

void init_rand(void) {
    const uint32_t seed = 56823605;//from random.org
    struct timespec spec;

    clock_gettime(CLOCK_REALTIME, &spec);
    srand48(seed + (spec.tv_nsec << 10));
}


uint32_t get_rand_num(void) {
    return (uint32_t) rand();
}

union RawArmInstruction get_rand_raw_instruction(void) {
    const uint32_t val = get_rand_num();
    return *(union RawArmInstruction *) &val;
}


struct ArmInstruction get_rand_instruction(void) {
    return ARMfromRaw(get_rand_raw_instruction());
}

struct ArmInstruction get_rand_instruction_of_types(enum ArmInstructionType *type, uint32_t arr_len) {
    while (true) {
        struct ArmInstruction instruction = get_rand_instruction();
        for (int i = 0; i < arr_len; ++i) {
            if (type[i] == instruction.type) {
                return instruction;
            }
            if(get_rand_num() < INT32_MAX/4){
                uint32_t val = ((*(uint32_t *)&instruction.rawArmInstruction) & ~(filler_mask[type[i]]) | filler_expected_values[type[i]]);
                return ARMfromRaw(*(union RawArmInstruction *)&val);

            }
        }
    }
}


void write_instructions_to_file(const char *name, struct ArmInstruction *instructions, uint32_t num_instructions) {
    FILE *fptr;
    fptr = fopen(name,"wb");
    for (int i = 0; i < num_instructions; ++i) {

        fwrite(&(instructions[i].rawArmInstruction),sizeof(union RawArmInstruction),1,fptr);
    }
    fclose(fptr);
}

enum ArmInstructionType fromString(const char* str){
    for (int i = 0; i < 15; ++i) {
        if(strcmp(str,type_to_string[i]) == 0){
            return (enum ArmInstructionType) i;
        }
    }
    assert(false);
}

#ifdef TEST_SCRIPT_MAIN

int main(uint32_t argc, const char **argv) {
    init_rand();
    do_asserts();
    assert(argc > 3);
    output_file = argv[1];
    assert(strtol(argv[2],NULL,10) > 0);
    uint64_t num_instructions = strtol(argv[2],NULL,10);
    uint32_t num_args = argc - 3;
    enum ArmInstructionType * types = calloc(15,sizeof(enum ArmInstructionType));
    for (int i = 3; i < argc; ++i) {
        enum ArmInstructionType instructionType = fromString(argv[i]);
        types[i - 3] = instructionType;
    }
    struct ArmInstruction* instructions = calloc(num_instructions, sizeof(struct ArmInstruction));
    for (int i = 0; i < num_instructions; ++i) {
        instructions[i] = get_rand_instruction_of_types(types,argc - 3);
    }
    write_instructions_to_file(output_file,instructions,num_instructions);
    free(types);
    free(instructions);
    return 0;

}

#endif