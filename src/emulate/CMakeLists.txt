cmake_minimum_required(VERSION 3.0)
project(emulate C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic")

add_executable(emulate emulate_main.c emulate_main.h instructions.c instructions.h)
set_target_properties(emulate
        PROPERTIES COMPILE_FLAGS "-DUSE_EMULATE_MAIN")