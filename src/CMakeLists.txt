cmake_minimum_required(VERSION 3.5)
project(src C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -g -O0 ")

add_executable(assemble
        assemble_dir/assemble.c
        assemble_dir/binary_file_writer.c
        assemble_dir/binary_file_writer.h
        assemble_dir/tokenizer.c
        assemble_dir/tokenizer.h
        shared/enums.h
        shared/instructions.h
        assemble_dir/symbol_table.h
        assemble_dir/symbol_table.c
        assemble_dir/extra_data.c
        assemble_dir/extra_data.h
        assemble_dir/utility.c
        assemble_dir/utility.h
        assemble_dir/parse/parseDataProcessing.c
        assemble_dir/parse/parseDataProcessing.h
        assemble_dir/parse/parseSingleDataTransfer.c
        assemble_dir/parse/parseSingleDataTransfer.h
        assemble_dir/parse/parseBranch.c
        assemble_dir/parse/parseBranch.h
        assemble_dir/parse/parseMultiply.c
        assemble_dir/parse/parseMultiply.h
        assemble_dir/parse/parseSpecial.c
        assemble_dir/parse/parseSpecial.h
        assemble_dir/parse/parseUtility.c
        assemble_dir/parse/parseUtility.h
        emulate_dir/emulate_main.h
        shared/common_structs.h assemble_dir/token.h)

add_executable(emulate
        emulate_dir/branch_instruction.c
        emulate_dir/cpsr_overflow_detection.c
        emulate_dir/cpsr_overflow_detection.h
        emulate_dir/data_processing_instruction.c
        emulate_dir/emulate_main.c
        emulate_dir/emulate_main.h
        emulate_dir/instructions.c
        shared/instructions.h
        emulate_dir/multiply_instruction.c
        emulate_dir/single_data_transfer_instruction.c
        shared/enums.h
        shared/common_structs.h)


add_executable(emulate_extension_
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
        emulate_extension/instructions/arm/halfword_and_signed_data_transfer.c
        emulate_extension/instructions/arm/halfword_and_signed_data_transfer.h
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
        emulate_extension/instructions/thumb/add_subtract.c
        emulate_extension/instructions/thumb/add_subtract.h
        emulate_extension/util/static_asserts.c
        emulate_extension/util/static_asserts.h
        emulate_extension/instructions/arm/single_data_transfer.c
        emulate_extension/instructions/arm/single_data_transfer.h
        emulate_extension/util/address.c
        emulate_extension/util/address.h
        emulate_extension/instructions/arm/block_data_transfer.c
        emulate_extension/instructions/arm/block_data_transfer.h
        emulate_extension/instructions/arm/software_interrupt.c
        emulate_extension/instructions/arm/software_interrupt.h
        emulate_extension/instructions/arm/branch.c
        emulate_extension/instructions/arm/branch.h
        emulate_extension/instructions/arm/branch_and_exchange.c
        emulate_extension/instructions/arm/branch_and_exchange.h
        emulate_extension/instructions/thumb/move_shifted_register.c
        emulate_extension/instructions/thumb/move_shifted_register.h
        emulate_extension/util/shift_util.c
        emulate_extension/util/shift_util.h
        emulate_extension/instructions/thumb/conditional_branch.c
        emulate_extension/instructions/thumb/conditional_branch.h
        emulate_extension/instructions/thumb/unconditional_branch.c
        emulate_extension/instructions/thumb/unconditional_branch.h
        emulate_extension/instructions/thumb/push_pop_registers.c
        emulate_extension/instructions/thumb/push_pop_registers.h
        emulate_extension/instructions/arm/coprocessor_data_operations.c
        emulate_extension/instructions/arm/coprocessor_data_operations.h
        emulate_extension/instructions/arm/coprocessor_data_transfers.c
        emulate_extension/instructions/arm/coprocessor_data_transfers.h
        emulate_extension/instructions/thumb/alu_operation.c
        emulate_extension/instructions/thumb/alu_operation.h
        emulate_extension/instructions/thumb/software_interrupt_thumb.c
        emulate_extension/instructions/thumb/software_interrupt_thumb.h
        emulate_extension/instructions/thumb/load_store_register_offset.c
        emulate_extension/instructions/thumb/load_store_register_offset.h
        emulate_extension/instructions/thumb/load_store_halfword.c
        emulate_extension/instructions/thumb/load_store_halfword.h
        emulate_extension/instructions/arm/coprocessor_register_transfer.c
        emulate_extension/instructions/arm/coprocessor_register_transfer.h
        emulate_extension/instructions/thumb/software_interrupt_thumb.h
        emulate_extension/instructions/thumb/load_store_register_offset.c
        emulate_extension/instructions/thumb/load_store_register_offset.h
        emulate_extension/instructions/thumb/load_store_halfword.c
        emulate_extension/instructions/thumb/load_store_halfword.h
        emulate_extension/instructions/thumb/move_compare_add_subtract.c
        emulate_extension/instructions/thumb/move_compare_add_subtract.h
        emulate_extension/instructions/thumb/conditional_branch.c
        emulate_extension/instructions/thumb/conditional_branch.h
        emulate_extension/instructions/thumb/unconditional_branch.c
        emulate_extension/instructions/thumb/unconditional_branch.h
        emulate_extension/instructions/arm/branch_and_exchange.h
        emulate_extension/instructions/thumb/PCRelativeLoad.c
        emulate_extension/instructions/thumb/PCRelativeLoad.h
        emulate_extension/instructions/thumb/Hi_register_operations_branch_exchange.c
        emulate_extension/instructions/thumb/Hi_register_operations_branch_exchange.h
        emulate_extension/instructions/arm/Undefined.c
        emulate_extension/instructions/arm/Undefined.h
        emulate_extension/instructions/thumb/load_store_sign_extended_byte_half_word.c
        emulate_extension/instructions/thumb/load_store_sign_extended_byte_half_word.h
        emulate_extension/instructions/arm/branch_and_exchange.h
        emulate_extension/instructions/thumb/PCRelativeLoad.c
        emulate_extension/instructions/thumb/PCRelativeLoad.h
        emulate_extension/instructions/thumb/Hi_register_operations_branch_exchange.c
        emulate_extension/instructions/thumb/Hi_register_operations_branch_exchange.h
        emulate_extension/instructions/arm/Undefined.c
        emulate_extension/instructions/arm/Undefined.h
        emulate_extension/instructions/arm/branch_and_exchange.h
        emulate_extension/instructions/thumb/move_shifted_register.c
        emulate_extension/instructions/thumb/move_shifted_register.h
        emulate_extension/instructions/thumb/move_compare_add_subtract.c
        emulate_extension/instructions/thumb/move_compare_add_subtract.h
        emulate_extension/instructions/thumb/conditional_branch.c
        emulate_extension/instructions/thumb/conditional_branch.h
        emulate_extension/instructions/thumb/unconditional_branch.c
        emulate_extension/instructions/thumb/unconditional_branch.h
        emulate_extension/instructions/thumb/SP_relative_load_store.c
        emulate_extension/instructions/thumb/SP_relative_load_store.h
        emulate_extension/instructions/thumb/multiple_load_store.c
        emulate_extension/instructions/thumb/multiple_load_store.h
        emulate_extension/instructions/thumb/long_branch_with_link.c
        emulate_extension/instructions/thumb/long_branch_with_link.h
        emulate_extension/instructions/thumb/load_store_with_immediate_offset.c
        emulate_extension/instructions/thumb/load_store_with_immediate_offset.h
        emulate_extension/state/exception.c
        emulate_extension/state/exception.h
        emulate_extension/main_loop.c
        emulate_extension/main_loop.h
        emulate_extension/util/entry_point.c
        emulate_extension/util/entry_point.h
        emulate_extension/instructions/arm/arm_instruction.c
        emulate_extension/instructions/arm/arm_instruction.h
        emulate_extension/test_generator.c
        emulate_extension/test_generator.h
        emulate_extension/instructions/arm/branch_and_exchange.h
        emulate_extension/instructions/thumb/move_shifted_register.c
        emulate_extension/instructions/thumb/move_shifted_register.h
        emulate_extension/util/shift_util.c
        emulate_extension/util/shift_util.h
        emulate_extension/state/exception.c
        emulate_extension/state/exception.h
        emulate_extension/main_loop.c
        emulate_extension/main_loop.h
        emulate_extension/util/entry_point.c
        emulate_extension/util/entry_point.h
        emulate_extension/instructions/arm/arm_instruction.c
        emulate_extension/instructions/arm/arm_instruction.h
        emulate_extension/instructions/arm/branch_and_exchange.h
        emulate_extension/instructions/thumb/move_shifted_register.c
        emulate_extension/instructions/thumb/move_shifted_register.h
        emulate_extension/util/shift_util.c
        emulate_extension/util/shift_util.h
        emulate_extension/instructions/thumb/move_compare_add_subtract.c
        emulate_extension/instructions/thumb/move_compare_add_subtract.h
        emulate_extension/instructions/thumb/conditional_branch.c
        emulate_extension/instructions/thumb/conditional_branch.h
        emulate_extension/instructions/thumb/unconditional_branch.c
        emulate_extension/instructions/thumb/unconditional_branch.h
        emulate_extension/instructions/thumb/SP_relative_load_store.c
        emulate_extension/instructions/thumb/SP_relative_load_store.h
        emulate_extension/instructions/thumb/multiple_load_store.c
        emulate_extension/instructions/thumb/multiple_load_store.h
        emulate_extension/instructions/thumb/long_branch_with_link.c
        emulate_extension/instructions/thumb/long_branch_with_link.h
        emulate_extension/instructions/thumb/load_store_with_immediate_offset.c
        emulate_extension/instructions/thumb/load_store_with_immediate_offset.h
        emulate_extension/state/exception.c
        emulate_extension/state/exception.h
        emulate_extension/instructions/thumb/thumb_instruction.c
        emulate_extension/instructions/thumb/load_address.c
        emulate_extension/instructions/thumb/load_address.h
        emulate_extension/instructions/thumb/thumb_instruction.h
        emulate_extension/instructions/arm/PSRTransfer.c
        emulate_extension/instructions/arm/PSRTransfer.h
        emulate_extension/dissasemble.c
        emulate_extension/dissasemble.h
        emulate_extension/mmu/mmu_main.c
        emulate_extension/mmu/mmu_main.h
        emulate_extension/mmu/domain.c
        emulate_extension/mmu/domain.h
        emulate_extension/mmu/supersection.c
        emulate_extension/mmu/supersection.h
        emulate_extension/mmu/coarse_page_table.c
        emulate_extension/mmu/coarse_page_table.h
        emulate_extension/mmu/section.c
        emulate_extension/mmu/section.h
        emulate_extension/mmu/extended_small_page.c
        emulate_extension/mmu/extended_small_page.h
        emulate_extension/mmu/small_page.c
        emulate_extension/mmu/small_page.h
        emulate_extension/mmu/large_page.c
        emulate_extension/mmu/large_page.h
        emulate_extension/persistant_storage/persistent_disk.c
        emulate_extension/persistant_storage/persistent_disk.h
        emulate_extension/sorta_a_bios/bootloader.c
        emulate_extension/sorta_a_bios/bootloader.h
        emulate_extension/mmu/serial_console.c
        emulate_extension/mmu/serial_console.h
        emulate_extension/instructions/thumb/add_offset_to_stack_pointer.h
        emulate_extension/instructions/thumb/add_offset_to_stack_pointer.c
        emulate_extension/instructions/arm/coprocessor_register_transfer.c
        emulate_extension/instructions/arm/coprocessor_register_transfer.h
        emulate_extension/coprocessor/system_control_coprocessor/system_control_and_configuration/c1_control.c
        emulate_extension/coprocessor/system_control_coprocessor/system_control_and_configuration/c1_control.h
        emulate_extension/coprocessor/system_control_coprocessor/system_control_and_configuration/c1_auxiliary_control.c
        emulate_extension/coprocessor/system_control_coprocessor/system_control_and_configuration/c1_auxiliary_control.h
        emulate_extension/coprocessor/system_control_coprocessor/system_control_and_configuration/c1_coprocessor_access_control.c
        emulate_extension/coprocessor/system_control_coprocessor/system_control_and_configuration/c1_coprocessor_access_control.h
        emulate_extension/coprocessor/system_control_coprocessor/system_control_and_configuration/c1_secure_configuration.c
        emulate_extension/coprocessor/system_control_coprocessor/system_control_and_configuration/c1_secure_configuration.h
        emulate_extension/coprocessor/system_control_coprocessor/system_control_and_configuration/c1_non_secure_access_control.c
        emulate_extension/mmu/serial_console.h
        emulate_extension/instructions/thumb/load_address.h
        emulate_extension/instructions/thumb/thumb_instruction.h
        emulate_extension/instructions/arm/PSRTransfer.c
        emulate_extension/instructions/arm/PSRTransfer.h
        emulate_extension/dissasemble.c
        emulate_extension/dissasemble.h
        emulate_extension/mmu/mmu_main.c
        emulate_extension/mmu/mmu_main.h
        emulate_extension/mmu/domain.c
        emulate_extension/mmu/domain.h
        emulate_extension/mmu/supersection.c
        emulate_extension/mmu/supersection.h
        emulate_extension/mmu/coarse_page_table.c
        emulate_extension/mmu/coarse_page_table.h
        emulate_extension/mmu/section.c
        emulate_extension/mmu/section.h
        emulate_extension/mmu/extended_small_page.c
        emulate_extension/mmu/extended_small_page.h
        emulate_extension/mmu/small_page.c
        emulate_extension/mmu/small_page.h
        emulate_extension/mmu/large_page.c
        emulate_extension/mmu/large_page.h
        emulate_extension/persistant_storage/persistent_disk.c
        emulate_extension/persistant_storage/persistent_disk.h
        emulate_extension/sorta_a_bios/bootloader.c
        emulate_extension/sorta_a_bios/bootloader.h
        emulate_extension/mmu/serial_console.c
        emulate_extension/coprocessor/system_control_coprocessor/system_control_and_configuration/c0_id_code.c
        emulate_extension/coprocessor/system_control_coprocessor/system_control_and_configuration/c0_id_code.h
        emulate_extension/coprocessor/system_control_coprocessor/system_control_and_configuration/c0_cache_type_register.c
        emulate_extension/coprocessor/system_control_coprocessor/system_control_and_configuration/c0_cache_type_register.h
        emulate_extension/mmu/translation.c
        emulate_extension/mmu/translation.h
        emulate_extension/mmu/address.c
        emulate_extension/mmu/address.h
        emulate_extension/coprocessor/system_control_coprocessor/system_control_and_configuration/c1_control.c
        emulate_extension/coprocessor/system_control_coprocessor/system_control_and_configuration/c1_control.h
        emulate_extension/coprocessor/system_control_coprocessor/system_control_and_configuration/c1_auxiliary_control.c
        emulate_extension/coprocessor/system_control_coprocessor/system_control_and_configuration/c1_auxiliary_control.h
        emulate_extension/coprocessor/system_control_coprocessor/system_control_and_configuration/c1_secure_configuration.c
        emulate_extension/coprocessor/system_control_coprocessor/system_control_and_configuration/c1_secure_configuration.h
        emulate_extension/coprocessor/system_control_coprocessor/system_control_and_configuration/c1_secure_debug_enable.c
        emulate_extension/coprocessor/system_control_coprocessor/system_control_and_configuration/c1_secure_debug_enable.h
        emulate_extension/coprocessor/system_control_coprocessor/system_control_and_configuration/c1_non_secure_access_control.c
        emulate_extension/coprocessor/system_control_coprocessor/system_control_and_configuration/c1_non_secure_access_control.h
        emulate_extension/coprocessor/system_control_coprocessor/system_control_and_configuration/c1_coprocessor_access_control.c
        emulate_extension/coprocessor/system_control_coprocessor/system_control_and_configuration/c1_coprocessor_access_control.h
        emulate_extension/coprocessor/system_control_coprocessor/system_control_and_configuration/c12_secure_or_non_secure_vector_base_address.c
        emulate_extension/coprocessor/system_control_coprocessor/system_control_and_configuration/c12_secure_or_non_secure_vector_base_address.h
        emulate_extension/coprocessor/system_control_coprocessor/system_control_and_configuration/c12_monitor_vector_base_address.c
        emulate_extension/coprocessor/system_control_coprocessor/system_control_and_configuration/c12_monitor_vector_base_address.h
        emulate_extension/coprocessor/system_control_coprocessor/system_control_and_configuration/c0_id_code.c
        emulate_extension/coprocessor/system_control_coprocessor/system_control_and_configuration/c0_id_code.h
        emulate_extension/coprocessor/system_control_coprocessor/system_control_and_configuration/c0_feature_id_cpuid_scheme.c
        emulate_extension/coprocessor/system_control_coprocessor/system_control_and_configuration/c0_feature_id_cpuid_scheme.h
        emulate_extension/coprocessor/system_control_coprocessor/mmu_control_and_configuration/c2_translation_table_base0.c
        emulate_extension/coprocessor/system_control_coprocessor/mmu_control_and_configuration/c2_translation_table_base0.h
        emulate_extension/coprocessor/system_control_coprocessor/mmu_control_and_configuration/c3_domain_access_control.h
        emulate_extension/coprocessor/system_control_coprocessor/mmu_control_and_configuration/c3_domain_access_control.c
        emulate_extension/coprocessor/system_control_coprocessor/mmu_control_and_configuration/c2_translation_table_base_control.c
        emulate_extension/coprocessor/system_control_coprocessor/mmu_control_and_configuration/c2_translation_table_base_control.h
        emulate_extension/coprocessor/system_control_coprocessor/mmu_control_and_configuration/c2_translation_table_base1.c
        emulate_extension/coprocessor/system_control_coprocessor/mmu_control_and_configuration/c2_translation_table_base1.h
        )
