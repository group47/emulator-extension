//
// Created by francis on 6/1/18.
//

#include <memory.h>
#include <stdio.h>
#include "emulator_main.h"
#include "util/static_asserts.h"
#include "util/entry_point.h"
#include "dissasemble.h"

#ifdef USE_EMULATOR_MAIN

static const char* binary_path;
static const char* invalid_arg;
static const char* logfile_path;

enum CommandLineFlags parseCommandLine(uint32_t argc, const char **argv){
    enum CommandLineFlags flags = (enum CommandLineFlags)0;
    for (int i = 1; i < argc; ++i) {
        const char* arg = argv[i];
        if(strcmp("--help",arg) == 0){
            flags |= HELP_MESSAGE;
        }else if(strcmp("-p",arg) == 0|| strcmp("--print-register-all",arg) == 0){
            flags |= DEBUG_PRINT_REGISTER;
        } else if(arg == strstr(arg,"--binary=")){
            binary_path = arg +  sizeof("--binary=")/sizeof(char) - 1;
        } else if(arg == strstr(arg,"--logfile=")){
            logfile_path = arg +  sizeof("--logfile=")/sizeof(char) - 1;
        } else if(0 == strcmp(arg,"-d") || 0 == strcmp(arg,"--disassemble")){
            flags |= DISASSEMBLE;
        } else{
            flags |= INVALID;
            invalid_arg = arg;
        }
    }
    flags |= TERMINATE_AFTER_200;//current default
    return flags;
}

int main(uint32_t argc, const char **argv){
    do_asserts();
    enum CommandLineFlags flags = parseCommandLine(argc,argv);
    if(flags & INVALID){
        fprintf(get_logfile(),"Invalid argument:");
        fprintf(get_logfile(),invalid_arg);
        fprintf(get_logfile(),"\n");
        return -1;
    }
    if(flags & HELP_MESSAGE){
        printf("Sorry no help message for now. look at the file emulator_main.c from the source.");//todo
        return 0;
    }
    if(flags & DISASSEMBLE){
        FILE* fp = fopen(binary_path,"r");
        if(fp == NULL){
            fprintf(stderr,"failed to open file\n");
            return -1;
        }
        disassemble(fp);
        fclose(fp);
    }
    FILE* fp = fopen(binary_path,"r");
    if(fp == NULL){
        fprintf(stderr,"failed to open file\n");
        return -1;
    }
    FILE* logfile = fopen(logfile_path,"w");
    if(logfile == NULL){
        logfile = stderr;
    }
    main_emulation_entry_point(flags,fp,logfile);
    fclose(fp);
    if(logfile != stderr){
        fclose(logfile);
    }



    //todo a more useful main
}

#endif


