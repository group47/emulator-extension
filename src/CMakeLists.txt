cmake_minimum_required(VERSION 3.10)
project(src C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -pedantic -g -DUSE_EMULATE_MAIN")


include_directories(assemble)
include_directories(emulate)

add_executable( assemble
        assemble/assemble.c
        assemble/binary_file_writer.c
        assemble/binary_file_writer.h
        assemble/list.c
        assemble/list.h
        assemble/symbol_table.c
        assemble/symbol_table.h
        assemble/tokenizer.c
        assemble/tokenizer.h)

add_executable( emulate
        emulate/branch_instruction.c
        emulate/branch_instruction.h
        emulate/cpsr_overflow_detection.c
        emulate/cpsr_overflow_detection.h
        emulate/data_processing_instruction.c
        emulate/data_processing_instruction.h
        emulate/emulate_main.c
        emulate/emulate_main.h
        emulate/instructions.c
        emulate/instructions.h
        emulate/multiply_instruction.c
        emulate/multiply_instruction.h
        emulate/single_data_transfer_instruction.c
        emulate/single_data_transfer_instruction.h)
