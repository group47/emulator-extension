cmake_minimum_required(VERSION 3.10)
project(emulate C)

set(CMAKE_C_STANDARD 99)

add_executable(output_instruction_types emulate_main.c emulate_main.h registers.cpp registers.h instructions.c instructions.h util.c util.h output_instruction_types.c output_instruction_types.h)