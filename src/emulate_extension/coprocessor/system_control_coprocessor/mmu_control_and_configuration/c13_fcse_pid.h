//
// Created by qs4617 on 07/06/18.
//

#ifndef SRC_C13_FCSE_PID_H
#define SRC_C13_FCSE_PID_H

struct C13_fcse_pid_register {
    uint32_t sbz : 25;
    uint8_t fcse_pid : 7;
}__attribute__((packed));

enum ExecutionExitCode execute_fcse_pid_register(struct CoprocessorRegisterTransferInstruction);

#endif //SRC_C13_FCSE_PID_H
