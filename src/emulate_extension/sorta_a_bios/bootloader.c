//
// Created by fpn17 on 11/06/18.
//

#include <stdlib.h>
#include <memory.h>
#include "bootloader.h"
#include "../state/emulator_state.h"
#include "../mmu/serial_console.h"
#include "../main_loop.h"
#include "../coprocessor/system_control_coprocessor/mmu_control_and_configuration/c2_translation_table_base0.h"
#include "../coprocessor/system_control_coprocessor/mmu_control_and_configuration/c3_domain_access_control.h"
#include "../coprocessor/system_control_coprocessor/mmu_control_and_configuration/c3_context_id_register.h"
#include "../util/static_asserts.h"
#include <sys/mman.h>
#include <fcntl.h>
#include <zconf.h>

static struct Memory prepared_ram;
static size_t atag_i = 0;

void append_atag(struct ATAG cmdline) {
    memcpy((prepared_ram.contents) + (PARAMETER_BLOCK_START_ADDRESS) + atag_i, &cmdline,
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

#define MEM_SIZE (1024 * 1024 * 1024)

void init_prepared_ram(FILE *kernel, enum CommandLineFlags flags) {
    if (flags & MMAP) {
        int fd = open("mem.bin", O_RDWR | O_CREAT, (mode_t) 0600);
        lseek(fd, MEM_SIZE * sizeof(uint8_t), SEEK_SET);
        write(fd, " ", 1);//create 1G file
        close(fd);
        fd = open("mem.bin", O_RDWR | O_CREAT, (mode_t) 0600);
        void *map = mmap(NULL, MEM_SIZE * sizeof(uint8_t), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
        prepared_ram.contents = map;
        memset(prepared_ram.contents, 0, MEM_SIZE * sizeof(uint8_t));
    } else {
        prepared_ram.contents = calloc(MEM_SIZE, sizeof(uint8_t));
    }
    prepared_ram.size = 1024 * 1024 * 1024 * sizeof(uint8_t);
    prepared_ram.mode = LITTLE_ENDIAN_;
    copy_kernel_into_ram(kernel);
    init_atags();
}

void init_registers(struct CPUState *state) {
    state->general_registers[0] = 0;
    state->general_registers[1] = (uint32_t) 0x00000183;//pretent to be a versatilepb for testing
    state->general_registers[2] = PARAMETER_BLOCK_START_ADDRESS;
    state->SPSR_abt.M = abt;
    state->SPSR_fiq.M = fiq;
    state->SPSR_svc.M = svc;
    state->SPSR_irq.M = irq;
    state->SPSR_und.M = und;
    //todo mmu and instruction/data cache turn off.
    state->CPSR.M = svc;
    state->CPSR.I = true;
    state->CPSR.F = true;
    state->CPSR.Z = true;//no idea why this is needed, but linux expects it so...
    state->CPSR.reserved = 1;//this doesn't do anything, but makes comparing with expected results easier
    set_word_in_register(PC_ADDRESS, KERNEL_LOAD_TO_ADDRESS);
    init_c1_control_register();
    init_c3_context_id_register();
    init_c2_translation_table_base_register0();
    init_C3_domain_access_control_register();

}


void boot(FILE *kernel, enum CommandLineFlags flags) {
    do_asserts();
    init_prepared_ram(kernel, flags);
    init_registers(getCPUState());
    set_memory(prepared_ram);
    main_loop(flags);
}

void boot_loader_entry_point(const char *image_path, enum CommandLineFlags flags) {
    FILE *img = fopen(image_path, "rb+");
    boot(img, flags);
}
