cmake_minimum_required(VERSION 3.7)
project(src C)

set(CMAKE_C_STANDARD 99)
#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -pedantic -g -DUSE_EMULATE_MAIN")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -pedantic -g -DUSE_EMULATE_MAIN -fsanitize=address")

add_executable(assemble
        assemble/assemble.c
        assemble/binary_file_writer.c
        assemble/binary_file_writer.h
        assemble/list.c
        assemble/list.h
        assemble/tokenizer.c
        assemble/tokenizer.h
        shared/enums.h
        shared/branch_instruction.h
        shared/data_processing_instruction.h
        shared/instructions.h
        assemble/symbol_table.h
        assemble/symbol_table.c
        shared/single_data_transfer_instruction.h
        assemble/extra_data.c
        assemble/extra_data.h
        assemble/utility.c
        assemble/utility.h
        assemble/parseDataProcessing.c
        assemble/parseDataProcessing.h
        assemble/parseSingleDataTransfer.c
        assemble/parseSingleDataTransfer.h
        assemble/parseBranch.c
        assemble/parseBranch.h
        assemble/parseMultiply.c
        assemble/parseMultiply.h
        assemble/parseSpecial.c
        assemble/parseSpecial.h
        assemble/parseUtility.c
        assemble/parseUtility.h)

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
        shared/single_data_transfer_instruction.h shared/enums.h)


add_executable(emulate_extension
        emulate_extension/emulator_main.c
        emulate_extension/emulator_main.h
        emulate_extension/state/memory.c
        emulate_extension/state/memory.h
        emulate_extension/basic_typedefs.h
        emulate_extension/instructions/arm/data_processing.c
        emulate_extension/instructions/arm/data_processing.h
        emulate_extension/instructions/arm/multiply.c
        emulate_extension/instructions/arm/multiply.h
        emulate_extension/instructions/arm/multiply_long.c
        emulate_extension/instructions/arm/multiply_long.h
        emulate_extension/instructions/arm/single_data_swap.c
        emulate_extension/instructions/arm/single_data_swap.h
        emulate_extension/state/emulator_state.c
        emulate_extension/state/emulator_state.h
        emulate_extension/util/overflow_util.c
        emulate_extension/util/overflow_util.h
        emulate_extension/util/cpsr_util.c
        emulate_extension/util/cpsr_util.h
        emulate_extension/util/operand_two_util.c
        emulate_extension/util/operand_two_util.h
        emulate_extension/util/common_enums.c
        emulate_extension/util/common_enums.h
        emulate_extension/instructions/thumb/add_subtract.c
        emulate_extension/instructions/thumb/add_subtract.h
        emulate_extension/util/static_asserts.c
        emulate_extension/util/static_asserts.h
        emulate_extension/instructions/arm/single_data_transfer.c
        emulate_extension/instructions/arm/single_data_transfer.h emulate_extension/util/address.c emulate_extension/util/address.h emulate_extension/instructions/arm/block_data_transfer.c emulate_extension/instructions/arm/block_data_transfer.h emulate_extension/instructions/arm/software_interrupt.c emulate_extension/instructions/arm/software_interrupt.h emulate_extension/instructions/arm/branch.c emulate_extension/instructions/arm/branch.h emulate_extension/instructions/arm/branch_and_exchange.c emulate_extension/instructions/arm/branch_and_exchange.h)
