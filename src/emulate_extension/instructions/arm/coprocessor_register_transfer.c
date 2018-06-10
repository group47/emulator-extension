//
// Created by fpn17 on 02/06/18.
//

#include <assert.h>
#include <stdio.h>
#include "../../util/entry_point.h"
#include "../../util/cpsr_util.h"

enum ExecutionExitCode
execute_copprocessor_register_transfer(struct CoprocessorRegisterTransferInstruction instruction) {
    if (!should_execute(instruction.cond)) {
        return DIDNT_EXECUTE;
    }

    fprintf(get_logfile(), "Coprocessor CP: %d\n", instruction.CP);
    fprintf(get_logfile(), "Coprocessor CPNum: %d\n", instruction.CPNum);
    fprintf(get_logfile(), "Coprocessor CPOpc: %d\n", instruction.CPOpc);
    fprintf(get_logfile(), "Coprocessor CRm: %d\n", instruction.CRm);
    fprintf(get_logfile(), "Coprocessor CRn: %d\n", instruction.CRn);
    fprintf(get_logfile(), "Coprocessor load/store bit: %d\n", instruction.loadStore);
    fprintf(get_logfile(), "Coprocessor Rd: %d\n", instruction.Rd);

    assert(false);
    switch (instruction.CPNum) {
        case 15:
            goto CPNum15;

        default:
            assert(false);
    }

    CPNum15:
      switch (instruction.CPOpc) {
          case 0:
              goto CPNum15_CPOpc0;

      }

    CPNum15_CPOpc0:
      switch (instruction.CRm) {
          case 0:
              goto CPNum15_CPOpc0_CRm0;
          case 1:
              goto CPNum15_CPOpc0_CRm1;
          default:
              assert(false);

      }

    CPNum15_CPOpc0_CRm0:
      switch (instruction.CP) {
          case 0:
              execute_co_main_id_register(instruction);
          case 1:
          case 2:
          case 3:
          default:
              assert(false);

      }

    CPNum15_CPOpc0_CRm1:



    CPNum15_CPOpc0_CRm3_7:
    assert(false);//todo implment

}
