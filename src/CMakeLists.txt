cmake_minimum_required(VERSION 3.7)
project(src C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -pedantic -g ")
#-fsanitize=fuzzer,address" )


include_directories(assemble)
include_directories(emulate)

add_executable(assemble
        assemble/assemble.c
        assemble/binary_file_writer.c
        assemble/binary_file_writer.h
        assemble/list.c
        assemble/list.h
        assemble/symbol_table.c
        assemble/symbol_table.h
        assemble/tokenizer.c
        assemble/tokenizer.h
        shared/enums.h
        shared/branch_instruction.h
        shared/data_processing_instruction.h
        shared/instructions.h
        shared/single_data_transfer_instruction.h emulate/rotate_right.c assemble/extra_data.c assemble/extra_data.h assemble/fuzzing_assemble.c emulate/rotate_right.h)

add_executable(emulate
        emulate/branch_instruction.c
        shared/branch_instruction.h
        emulate/cpsr_overflow_detection.c
        emulate/cpsr_overflow_detection.h
        emulate/data_processing_instruction.c
        shared/data_processing_instruction.h
        emulate/emulate_main.c
        emulate/emulate_main.h
        emulate/instructions.c
        shared/instructions.h
        emulate/multiply_instruction.c
        shared/multiply_instruction.h
        emulate/single_data_transfer_instruction.c
        shared/single_data_transfer_instruction.h shared/enums.h
        emulate/fuzzing_emulate.c emulate/rotate_right.c emulate/rotate_right.h)
