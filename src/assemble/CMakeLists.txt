cmake_minimum_required(VERSION 3.8)
project(assemble)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES assemble.c list.c binary_file_writer.c tokenizer.c symbol_table.h )
add_executable(assemble ${SOURCE_FILES})