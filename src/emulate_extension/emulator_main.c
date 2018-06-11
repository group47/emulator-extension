//
// Created by francis on 6/1/18.
//

#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
#include "util/static_asserts.h"
#include "util/entry_point.h"
#include "emulator_main.h"
#include "dissasemble.h"
#include "sorta_a_bios/bootloader.h"

#ifdef USE_EMULATOR_MAIN

static const char *binary_path = "";
static const char *kernel_path = "";
static const char *invalid_arg = "";
static const char *logfile_path = "";
static const char *sp_print_offset = "0";
static const char *pc_print_offset = "0";
static enum CommandLineFlags globalFlags;

enum CommandLineFlags parseCommandLine(int argc, const char **argv) {
    enum CommandLineFlags flags = (enum CommandLineFlags) 0;
    for (int i = 1; i < argc; ++i) {
        const char *arg = argv[i];
        if (strcmp("--help", arg) == 0) {
            flags |= HELP_MESSAGE;
        } else if (strcmp("-p", arg) == 0 || strcmp("--print-register-all", arg) == 0) {
            flags |= DEBUG_PRINT_REGISTER;
        } else if (arg == strstr(arg, "--binary=")) {
            binary_path = arg + sizeof("--binary=") / sizeof(char) - 1;
        } else if (arg == strstr(arg, "--logfile=")) {
            logfile_path = arg + sizeof("--logfile=") / sizeof(char) - 1;
        } else if (0 == strcmp(arg, "-d") || 0 == strcmp(arg, "--disassemble")) {
            flags |= DISASSEMBLE;
        } else if (0 == strcmp(arg, "-m")) {
            flags |= MEMORY;
        } else if (0 == strcmp(arg, "--thumb")) {
            flags |= USE_THUMB;
        } else if (arg == strstr(arg, "--sp-print-offset=")) {
            sp_print_offset = arg + sizeof("--sp-print-offset=") / sizeof(char) - 1;
            flags |= SP_PRINT_OFFSET_SET;
        } else if (arg == strstr(arg, "--pc-print-offset=")) {
            pc_print_offset = arg + sizeof("--pc-print-offset=") / sizeof(char) - 1;
            flags |= PC_PRINT_OFFSET_SET;
        } else if (arg == strstr(arg, "--kernel=")) {
            kernel_path = arg + sizeof("--kernel=") / sizeof(char) - 1;
            flags |= KERNEL;
        } else if (0 == strcmp(arg, "--zimage")) {
            flags |= ZIMAGE;
        } else {
            flags |= INVALID;
            invalid_arg = arg;
        }
    }
    flags |= TERMINATE_AFTER_200;//current default
    return flags;
}

int main(int argc, const char **argv) {
    do_asserts();
    enum CommandLineFlags flags = parseCommandLine(argc, argv);
    globalFlags = flags;
    if (flags & INVALID) {
        fprintf(get_logfile(), "Invalid argument:");
        fprintf(get_logfile(), invalid_arg);
        fprintf(get_logfile(), "\n");
        return -1;
    }
    if (flags & HELP_MESSAGE) {
        printf("Sorry no help message for now. look at the file emulator_main.c from the source.");//todo
        return 0;
    }
    if (flags & DISASSEMBLE) {
        FILE *fp = fopen(binary_path, "r");
        if (fp == NULL) {
            fprintf(stderr, "failed to open file\n");
            return -1;
        }
        disassemble(fp);
        fclose(fp);
    }
    if (flags & KERNEL) {
        boot_loader_entry_point(kernel_path, flags);
    }
    FILE *fp = fopen(binary_path, "r");
    if (fp == NULL) {
        fprintf(stderr, "failed to open file\n");
        return -1;
    }
    FILE *logfile = fopen(logfile_path, "w");
    if (logfile == NULL) {
        logfile = stderr;
    }
    main_emulation_entry_point(flags, fp, logfile);
    fclose(fp);
    if (logfile != stderr) {
        fclose(logfile);
    }
}

#endif


long parse_num(char *str) {
    char *check_valid = "\0";
    long res = strtol(str, &check_valid, 10);
    if (check_valid[0] != '\0') {
        fprintf(stderr, "Warning: Invalid numeric parameter passed.");
        return 0;
    }
    return res;
}

long get_sp_offset() {
    return parse_num((char *) sp_print_offset);
}


long get_pc_offset() {
    return parse_num((char *) pc_print_offset);
}


