
This repository contains three seperate but related C Programs, that can be compiled with the `CMakeLists.txt` in `src/`. The first two where written to a specification as part of a first year project at Imperial College London. The last one is an optional extension.

## emulate
Emulates an running an arm binary on a bare metal raspberry pi. Only implements a subset of armv6 instructions, has no coprocessor/MMU support. Can additionally detect if address associated with GPIO pins have been accessed and print a message accordingly.

## assemble
An armv6 assember, which also supports a limited subset of instructions.

## emulate_extension
An extended emulator created with the goal of booting linux, on the emulator. Supports all armv6 instructions(both arm and thumb), and has some coprocessor support, as well as MMU support. Has the following options:

OPTIONS [-p][-d][--binary=$<$path$>$][--logfile=$<$path$>$][--kernel=$<$path$>$][--thumb]

--binary Directory of a binary file to run. 

--logfile Directory of a log file which records register values. 

--kernel Attempt to boot the specified kernel, by loading the kernel into memory and executing it. 

--thumb Interpret instructions as THUMB instructions, otherwise instructions are interpreted as ARM instructions by default.

-p Print the state of registers after each executed instruction. 

-d Print the type of the instruction being executed. 
