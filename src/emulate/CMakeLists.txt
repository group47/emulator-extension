cmake_minimum_required(VERSION 3.0)
project(emulate C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -pedantic -g -fsanitize=address")

add_executable(emulate emulate_main.c emulate_main.h instructions.c instructions.h cpsr_overflow_detection.c cpsr_overflow_detection.h)
set_target_properties(emulate
        PROPERTIES COMPILE_FLAGS "-DUSE_EMULATE_MAIN")