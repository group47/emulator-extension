//
// Created by qs4617 on 07/06/18.
//

#ifndef SRC_SYSTEM_CONTROL_COPROCESSOR_H
#define SRC_SYSTEM_CONTROL_COPROCESSOR_H

#include "system_control_and_configuration/c1_control.h"
#include "system_control_and_configuration/c1_auxiliary_control.h"
#include "system_control_and_configuration/c1_secure_configuration.h"
#include "system_control_and_configuration/c1_secure_debug_enable.h"
#include "system_control_and_configuration/c1_non_secure_access_control.h"
#include "system_control_and_configuration/c1_coprocessor_access_control.h"
#include "system_control_and_configuration/c12_secure_or_non_secure_vector_base_address.h"
#include "system_control_and_configuration/c0_id_code.h"
#include "system_control_and_configuration/c0_feature_id_cpuid_scheme.h"
#include "../../basic_typedefs.h"

struct SystemControlCoprocessor {

    // system_control_and_configuration_registers
    struct C1_control_register c1_control_register;
    struct C1_auxiliary_control_register c1_auxiliary_control_register;
    struct C1_secure_configuration_register c1_secure_configuration_register;
    struct C1_secure_debug_enable_register c1_secure_debug_enable_register;
    struct C1_none_secure_access_control_register c1_none_secure_access_control_register;
    struct C1_coprocessor_access_control_register c1_coprocessor_access_control_register;
    struct C12_secure_or_non_secure_vector_base_address_register c12_secure_or_non_secure_vector_base_address_register;
    struct C0_main_id_register c0_main_id_register;
    struct C0_cpuid_register c0_cpuid_register;
//    struct c0_tlb_type_register c0_tlb_type_register_;
//    struct C2_translation_table_base_register0 c2_translation_table_base_register0;
//    struct C2_translation_table_base_register1 c2_translation_table_base_register1;
//    struct C2_translation_table_base_control_register c2_translation_table_base_control_register;
//    struct C3_domain_access_control_register c3_domain_access_control_register;
//    struct C5_data_fault_status_register c5_data_fault_status_register;
//    struct C5_instruction_fault_status_register c5_instruction_fault_status_register;
//    struct C6_fault_address_register c6_fault_address_register;
//    struct C6_instruction_fault_address_register c6_instruction_fault_address_register;
//    struct C6_watchpoint_fault_address_register c6_watchpoint_fault_address_register;
//    struct C8_tlb_operations_register c8_tlb_operations_register;
};


enum CoprocessorRegisterType {
    REGISTER_TYPE_C1_CONTROL,
    REGISTER_TYPE_C1_AUXILIARY_CONTROL,
    REGISTER_TYPE_C1_SECURE_CONFIGURATION,
    REGISTER_TYPE_C1_SECURE_DEBUG_ENABLE,
    REGISTER_TYPE_C1_NONE_SECURE_ACCESS_CONTROL,
    REGISTER_TYPE_C1_COPROCESSOR_ACCESS_CONTROL,
    REGISTER_TYPE_C12_SECURE_OR_NON_SECURE_VECTOR_BASE_ADDRESS,
    REGISTER_TYPE_C0_MAIN_ID,
    REGISTER_TYPE_C0_CPUID
};

void set_word_in_system_control_coprocessor_register(Word val);


#endif //SRC_SYSTEM_CONTROL_COPROCESSOR_H
