//
// Created by fpn17 on 02/06/18.
//

#include <assert.h>
#include "coprocessor_register_transfer.h"
#include "../../coprocessor/system_control_coprocessor/system_control_and_configuration/c0_id_code.h"


enum ExecutionExitCode execute_copprocessor_register_transfer(struct CoprocessorRegisterTransferInstruction instruction){
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


}