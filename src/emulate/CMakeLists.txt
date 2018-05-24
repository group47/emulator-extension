cmake_minimum_required(VERSION 3.10)
project(emulate C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic")



add_executable(emulate_main emulate_main.c emulate_main.h registers.cpp registers.h instructions.c instructions.h util.c util.h output_instruction_types.c output_instruction_types.h)
set_target_properties(emulate_main
        PROPERTIES COMPILE_FLAGS "-DUSE_EMULATE_MAIN")
#add_definitions("-DUSE_EMULATE_MAIN")


add_executable(output_instruction_types emulate_main.c emulate_main.h registers.cpp registers.h instructions.c instructions.h util.c util.h output_instruction_types.c output_instruction_types.h)
set_target_properties(output_instruction_types
        PROPERTIES COMPILE_FLAGS "-DUSE_EMULATE_MAIN")
#add_definitions("-DINSTRUCTION_TYPES_TEST")
