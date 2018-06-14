//
// Created by fpn17 on 11/06/18.
//

#include <stdlib.h>
#include <memory.h>
#include "bootloader.h"
#include "../state/emulator_state.h"
#include "../mmu/serial_console.h"
#include "../main_loop.h"

static struct Memory prepared_ram;
static size_t atag_i = 0;

void append_atag(struct ATAG cmdline) {
    memcpy((prepared_ram.contents) + (PARAMETER_BLOCK_START_ADDRESS - MEMORY_OFFSET) + atag_i, &cmdline,
           cmdline.header.size * sizeof(Word));
    atag_i += cmdline.header.size * sizeof(Word);
}

void init_core() {
    struct ATAG core;
    core.header.tag = ATAG_TAG_CORE;
    core.header.size = 5;
    core.core.flags = 1;
    core.core.pagesize = 4096;
    core.core.rootdev = 0;
    append_atag(core);

}

void init_mem() {
    struct ATAG mem;
    mem.header.tag = ATAG_TAG_MEM;
    mem.header.size = 4;
    mem.mem.size = 1024 * 1024 * 1024;//one gigabyte
    mem.mem.start = 0x0;
    append_atag(mem);
}

void init_serial() {
    struct ATAG serial;
    serial.header.tag = ATAG_TAG_SERIAL;
    serial.header.size = 4;
    serial.serial.serial_num = 666;//this number does  not matter at all. It can be literally anything
    append_atag(serial);
}

void init_cmdline() {
    struct ATAG cmdline;
    cmdline.header.tag = ATAG_TAG_CMDLINE;
    const char *cmdline_params = "console=uart8250,0x%x";
    sprintf(cmdline.atag_cmdline.cmdline, cmdline_params, MAGIC_CONSOLE_ADDRESS);
    cmdline.header.size = (uint32_t) (2 + (strlen(cmdline.atag_cmdline.cmdline) + 3) / 4);
    append_atag(cmdline);
}

void init_atag_none() {
    struct ATAG none;
    none.header.size = 2;
    none.header.tag = ATAG_TAG_NONE;
    append_atag(none);
}

void atag_ramdisk() {
    //todo
}

void init_serial_revision() {
    struct ATAG serial;
    serial.header.tag = ATAG_TAG_REVISION;
    serial.header.size = 3;
    serial.revision.rev = 666;//this number does  not matter at all. It can be literally anything
    append_atag(serial);
}

void init_atags() {
    init_core();
    init_mem();
    init_cmdline();
    init_serial();
    init_serial_revision();
    atag_ramdisk();
    init_atag_none();
}

bool check_magic_number(Word val) {
    return val == MAGIC_ARM_BOOT_NUMBER;
}

void copy_kernel_into_ram(FILE *kernel) {
    Byte current_word;
    uint32_t ram_i = 0;
    while (fread(&current_word, sizeof(Byte), 1, kernel)) {
        (prepared_ram.contents)[ram_i + KERNEL_LOAD_TO_ADDRESS] = current_word;
        ram_i++;
    }

}

void init_prepared_ram(FILE *kernel) {
    prepared_ram.contents = calloc(1024 * 1024 * 1024, sizeof(uint8_t));
    prepared_ram.size = 1024 * 1024 * 1024 * sizeof(uint8_t);
    prepared_ram.mode = LITTLE_ENDIAN_;
    copy_kernel_into_ram(kernel);
    init_atags();
}

void init_registers(struct CPUState *state) {
    state->general_registers[0] = 0;
    state->general_registers[1] = (uint32_t) 0x00000183;//pretent to be a versatilepb for testing
    state->general_registers[2] = PARAMETER_BLOCK_START_ADDRESS;
    //todo mmu and instruction/data cache turn off.
    state->CPSR.M = svc;
    state->CPSR.I = true;
    state->CPSR.F = true;
    state->CPSR.Z = true;//no idea why this is needed, but linux expects it so...
    state->CPSR.reserved = 1;//this doesn't do anything, but makes comparing with expected results easier
    set_word_in_register(PC_ADDRESS, KERNEL_LOAD_TO_ADDRESS + MEMORY_OFFSET);
    init_c1_control_register();

}


void boot(FILE *kernel, enum CommandLineFlags flags) {
    init_prepared_ram(kernel);
    init_registers(getCPUState());
    set_memory(prepared_ram);
    main_loop(flags);
}

void boot_loader_entry_point(const char *image_path, enum CommandLineFlags flags) {
    FILE *img = fopen(image_path, "rb+");
    boot(img, flags);
}
