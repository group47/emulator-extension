//
// Created by fpn17 on 02/06/18.
//

#include <assert.h>
#include <stdio.h>
#include "coprocessor_register_transfer.h"
#include "../../util/entry_point.h"
#include "../../coprocessor/system_control_coprocessor/system_control_coprocessor.h"
#include "../../util/cpsr_util.h"

enum ExecutionExitCode execute_copprocessor_register_transfer(struct CoprocessorRegisterTransferInstruction instruction) {
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

//    assert(false);
//    return OK;
    switch (instruction.CPNum) {
        case 15:
            goto CPNum15;

        default:
            assert(false);
    }


    CPNum15:
    switch (instruction.CRn) {
        case 0:
            goto CPNum15_CRn0;
        case 1 :
            goto CPNum15_CRn1;
        case 2 :
            goto CPNum15_CRn2;
        case 3 :
            goto CPNum15_CRn3;
        case 5 :
            goto CPNum15_CRn5;
        case 6 :
            goto CPNum15_CRn6;
        case 7 :
            goto CPNum15_CRn7;
        case 8 :
            goto CPNum15_CRn8;
        case 9 :
            goto CPNum15_CRn9;
        case 10 :
            goto CPNum15_CRn10;
        case 11 :
            goto CPNum15_CRn11;
        case 12 :
            goto CPNum15_CRn12;
        case 13 :
            goto CPNum15_CRn13;
        case 15:
            goto CPNum15_CRn15;
        default:
            assert(false);
    }

    // ========================================================================

    CPNum15_CRn0:
    switch (instruction.CPOpc) {
        case 0:
            goto CPNum15_CRn0_CPOpc0;
        default:
            assert(false);

    }
    CPNum15_CRn1:
    switch (instruction.CPOpc) {
        case 0:
            goto CPNum15_CRn1_CPOpc0;
        default:
            assert(false);
    }
    
    CPNum15_CRn2:
    switch (instruction.CPOpc) {
        case 0:
            goto CPNum15_CRn2_CPOpc0;
        default:
            assert(false);
    }

    CPNum15_CRn3:
    switch (instruction.CPOpc) {
        case 0:
            goto CPNum15_CRn3_CPOpc0;
        default:
            assert(false);
    }
    CPNum15_CRn5:
    switch (instruction.CPOpc) {
        case 0:
            goto CPNum15_CRn5_CPOpc0;
        default:
            assert(false);
    }

    CPNum15_CRn6:
    switch (instruction.CPOpc) {
        case 0:
            goto CPNum15_CRn6_CPOpc0;
        default:
            assert(false);
    }

    CPNum15_CRn7:
    switch (instruction.CPOpc) {
        case 0:
            goto CPNum15_CRn7_CPOpc0;
        default:
            assert(false);
    }

    CPNum15_CRn8:
    switch (instruction.CPOpc) {
        case 0:
            goto CPNum15_CRn8_CPOpc0;
        default:
            assert(false);
    }

    CPNum15_CRn9:
    switch (instruction.CPOpc) {
        case 0:
            goto CPNum15_CRn9_CPOpc0;
        default:
            assert(false);
    }

    CPNum15_CRn10:
    switch (instruction.CPOpc) {
        case 0:
            goto CPNum15_CRn10_CPOpc0;
        default:
            assert(false);
    }

    CPNum15_CRn11:
    switch (instruction.CPOpc) {
        case 0:
            goto CPNum15_CRn11_CPOpc0;
        default:
            assert(false);
    }

    CPNum15_CRn12:
    switch (instruction.CPOpc) {
        case 0:
            goto CPNum15_CRn12_CPOpc0;
        default:
            assert(false);
    }

    CPNum15_CRn13:
    switch (instruction.CPOpc) {
        case 0:
            goto CPNum15_CRn13_CPOpc0;
        default:
            assert(false);
    }

    CPNum15_CRn15:
    switch (instruction.CPOpc) {
        case 0:
            goto CPNum15_CRn15_CPOpc0;
        case 1:
            goto CPNum15_CRn15_CPOpc1;
        case 2:
            goto CPNum15_CRn15_CPOpc2;
        case 3:
            goto CPNum15_CRn15_CPOpc3;
        case 4:
            goto CPNum15_CRn15_CPOpc4;
        case 5:
            goto CPNum15_CRn15_CPOpc5;
        case 6:
            goto CPNum15_CRn15_CPOpc6;
        case 7:
            goto CPNum15_CRn15_CPOpc7;
        default:
            assert(false);
    }



    //=======================================================================


    CPNum15_CRn0_CPOpc0:
    switch (instruction.CRm) {
        case 0:
            goto CPNum15_CRn0_CPOpc0_CRm0;
        case 1:
            goto CPNum15_CRn0_CPOpc0_CRm1;
        case 2:
            goto CPNum15_CRn0_CPOpc0_CRm2;
        default:
            if (instruction.CRm < 0|| instruction.CRm >= 7) {
                goto CPNum15_CRn0_CPOpc0_CRm3_7;
            }
            return OK;
    }


    CPNum15_CRn1_CPOpc0:
      switch (instruction.CRm) {
          case 0:
              goto CPNum15_CRn1_CPOpc0_CRm0;
          case 1:
              goto CPNum15_CRn1_CPOpc0_CRm1;
          default:
              assert(false);
      }



    CPNum15_CRn1_CPOpc1:
    switch(instruction.CRm) {
        case 0:
            goto CPNum15_CRn1_CPOpc0_CRm0;
        case 1:
            goto CPNum15_CRn1_CPOpc0_CRm1;
        default:
            assert(false);
    }

    CPNum15_CRn2_CPOpc0:
    switch (instruction.CRm) {
        case 0:
            goto CPNum15_CRn2_CPOpc0_CRm0;
    }

    CPNum15_CRn3_CPOpc0:
    switch (instruction.CRm) {
        case 0:
            goto CPNum15_CRn3_COpc0_CRm0;
        default:
            assert(false);
    }

    CPNum15_CRn5_CPOpc0:
    switch (instruction.CRm) {
        case 0:
            goto CPNum15_CRn5_COpc0_CRm0;

    }

    CPNum15_CRn6_CPOpc0:
    switch (instruction.CRm) {
        case 0:
            goto CPNum15_CRn6_COpc0_CRm0;
    }

    CPNum15_CRn7_CPOpc0:
    switch (instruction.CRm) {
        case 0:
            goto CPNum15_CRn7_COpc0_CRm0;
        case 4:
            goto CPNum15_CRn7_COpc0_CRm4;
        case 5:
            goto CPNum15_CRn7_COpc0_CRm5;
        case 6:
            goto CPNum15_CRn7_COpc0_CRm6;
        case 7:
            goto CPNum15_CRn7_COpc0_CRm7;
        case 8:
            goto CPNum15_CRn7_COpc0_CRm8;
        case 10:
            goto CPNum15_CRn7_COpc0_CRm10;
        case 13:
            goto CPNum15_CRn7_COpc0_CRm13;
        case 14:
            goto CPNum15_CRn7_COpc0_CRm14;
        default:
            assert(false);
    }

    CPNum15_CRn8_CPOpc0:
    switch (instruction.CRm) {
        case 5:
            goto CPNum15_CRn8_COpc0_CRm5;
        case 6:
            goto CPNum15_CRn8_COpc0_CRm6;
        case 7:
            goto CPNum15_CRn8_COpc0_CRm7;
        default:
            assert(false);
    }

    CPNum15_CRn9_CPOpc0:
    switch (instruction.CRm) {
        case 0:
            goto CPNum15_CRn9_COpc0_CRm0;
        case 1:
            goto CPNum15_CRn9_COpc0_CRm1;
        case 2:
            goto CPNum15_CRn9_COpc0_CRm2;
        case 8:
            goto CPNum15_CRn9_COpc0_CRm8;
        default:
            assert(false);
    }

    CPNum15_CRn10_CPOpc0:
    switch (instruction.CRm) {
        case 0:
            goto CPNum15_CRn10_COpc0_CRm0;
        case 2:
            goto CPNum15_CRn10_COpc0_CRm2;
        default:
            assert(false);
    }

    CPNum15_CRn11_CPOpc0:
    switch (instruction.CRm) {
        case 0:
            goto CPNum15_CRn11_COpc0_CRm0;
        case 1:
            goto CPNum15_CRn11_COpc0_CRm1;
        case 2:
            goto CPNum15_CRn11_COpc0_CRm2;
        case 3:
            goto CPNum15_CRn11_COpc0_CRm3;
        case 4:
            goto CPNum15_CRn11_COpc0_CRm4;
        case 5:
            goto CPNum15_CRn11_COpc0_CRm5;
        case 6:
            goto CPNum15_CRn11_COpc0_CRm6;
        case 7:
            goto CPNum15_CRn11_COpc0_CRm7;
        case 8:
            goto CPNum15_CRn11_COpc0_CRm8;
        case 15:
            goto CPNum15_CRn11_COpc0_CRm15;
        default:
            assert(false);
    }

    CPNum15_CRn12_CPOpc0:
    switch (instruction.CRm) {
        case 0:
            goto CPNum15_CRn12_COpc0_CRm0;
        case 1:
            goto CPNum15_CRn12_COpc0_CRm1;
        default:
            assert(false);
    }

    CPNum15_CRn13_CPOpc0:
    switch (instruction.CRm) {
        case 0:
            goto CPNum15_CRn13_COpc0_CRm0;
        default:
            assert(false);
    }

    CPNum15_CRn15_CPOpc0:
    switch (instruction.CRm) {
        case 2:
            goto CPNum15_CRn15_COpc0_CRm2;
        case 9:
            goto CPNum15_CRn15_COpc0_CRm9;
        case 12:
            goto CPNum15_CRn15_COpc0_CRm12;
        case 13:
            goto CPNum15_CRn15_COpc0_CRm13;
        case 14:
            goto CPNum15_CRn15_COpc0_CRm14;
        default:
            assert(false);
    }

    CPNum15_CRn15_CPOpc1:
    switch (instruction.CRm) {
        case 13:
            goto CPNum15_CRn15_COpc1_CRm13;
        default:
            assert(false);
    }
    CPNum15_CRn15_CPOpc2:
    switch (instruction.CRm) {
        case 13:
            goto CPNum15_CRn15_COpc2_CRm13;
        default:
            assert(false);
    }

    CPNum15_CRn15_CPOpc3:
    switch (instruction.CRm) {
        case 8:
            goto CPNum15_CRn15_COpc3_CRm8;
        case 12:
            goto CPNum15_CRn15_COpc3_CRm12;
        case 13:
            goto CPNum15_CRn15_COpc3_CRm13;
        default:
            assert(false);
    }

    CPNum15_CRn15_CPOpc4:
    switch (instruction.CRm) {
        case 13:
            goto CPNum15_CRn15_COpc4_CRm13;
        default:
            assert(false);
    }

    CPNum15_CRn15_CPOpc5:
    switch (instruction.CRm) {
        case 4:
            goto CPNum15_CRn15_COpc5_CRm4;
        case 5:
            goto CPNum15_CRn15_COpc5_CRm5;
        case 6:
            goto CPNum15_CRn15_COpc5_CRm6;
        case 7:
            goto CPNum15_CRn15_COpc5_CRm7;
        default:
            assert(false);
    }

    CPNum15_CRn15_CPOpc6:
    switch (instruction.CRm) {
        case 13:
            goto CPNum15_CRn15_COpc6_CRm13;
        default:
            assert(false);
    }

    CPNum15_CRn15_CPOpc7:
    switch (instruction.CRm) {
        case 13:
            goto CPNum15_CRn15_COpc7_CRm13;
        default:
            assert(false);
    }


    //=========================================================================


    CPNum15_CRn0_CPOpc0_CRm0:
    switch (instruction.CP) {
        case 0: {
            struct C0_main_id_register val = get_main_id_register();
            set_word_in_register(instruction.Rd, *(uint32_t *) &val);
            return OK;
        }
        case 1:
        case 2:
        case 3:
        default:
            assert(false);
    }
    CPNum15_CRn0_CPOpc0_CRm1:
    switch (instruction.CP) {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        default:
            assert(false);
    }

    CPNum15_CRn0_CPOpc0_CRm2:
    switch (instruction.CP) {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        default:
            assert(false);
    }
    CPNum15_CRn0_CPOpc0_CRm3_7:
    assert(false);

    CPNum15_CRn1_CPOpc0_CRm0:
    switch (instruction.CP) {
        case 0:
            return execute_control_register(instruction);
        case 1:
            return execute_co_auxiliary_control_register(instruction);
        case 2:
            return execute_coprocessor_access_control(instruction);
        default:
            assert(false);
    }


    CPNum15_CRn1_CPOpc0_CRm1:
    switch (instruction.CP) {
        case 0:
            return execute_secure_configuration_register(instruction);
        case 1:
            assert(false);
        case 2:
            return execute_none_secure_access_control_register(instruction);
        default:
            assert(false);
    }



    CPNum15_CRn2_CPOpc0_CRm0:
    switch (instruction.CP) {
        case 0:
        case 1:
        case 2:
        default:
            assert(false);
    }


    CPNum15_CRn3_COpc0_CRm0:
    switch (instruction.CP) {
        case 0:
        default:
            assert(false);
    }

    CPNum15_CRn5_COpc0_CRm0:
    switch (instruction.CP) {
        case 0:
        case 1:
        default:
            assert(false);
    }

    CPNum15_CRn6_COpc0_CRm0:
    switch (instruction.CP) {
        case 0:
        case 1:
        case 2:
        default:
            assert(false);
    }

    CPNum15_CRn7_COpc0_CRm0:
    switch (instruction.CP) {
        case 4:
        default:
            assert(false);
    }

    CPNum15_CRn7_COpc0_CRm4:
    switch (instruction.CP) {
        case 0:
        default:
            assert(false);
    }

    CPNum15_CRn7_COpc0_CRm5:
    switch (instruction.CP) {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 6:
        case 7:
        default:
            assert(false);
    }

    CPNum15_CRn7_COpc0_CRm6:
    switch (instruction.CP) {
        case 0:
        case 1:
        case 2:
        default:
            assert(false);
    }

    CPNum15_CRn7_COpc0_CRm7:
    switch (instruction.CP) {
        case 0:
        default:
            assert(false);
    }

    CPNum15_CRn7_COpc0_CRm8:
    switch (instruction.CP) {
        default:
            assert(false);
    }

    CPNum15_CRn7_COpc0_CRm10:
    switch (instruction.CP) {
        case 0:
        case 1:
        case 2:
        case 4:
        case 5:
        case 6:
        default:
            assert(false);
    }

    CPNum15_CRn7_COpc0_CRm13:
    switch (instruction.CP) {
        case 1:
        default:
            assert(false);
    }

    CPNum15_CRn7_COpc0_CRm14:
    switch (instruction.CP) {
        case 0:
        case 1:
        case 2:
        default:
            assert(false);
    }

    CPNum15_CRn8_COpc0_CRm5:
    switch (instruction.CP) {
        case 0:
        case 1:
        case 2:
        default:
            assert(false);
    }

    CPNum15_CRn8_COpc0_CRm6:
    switch (instruction.CP) {
        case 0:
        case 1:
        case 2:
        default:
            assert(false);
    }

    CPNum15_CRn8_COpc0_CRm7:
    switch (instruction.CP) {
        case 0:
        case 1:
        case 2:
        default:
            assert(false);
    }

    CPNum15_CRn9_COpc0_CRm0:
    switch (instruction.CP) {
        case 0:
        case 1:
        default:
            assert(false);
    }

    CPNum15_CRn9_COpc0_CRm1:
    switch (instruction.CP) {
        case 0:
        case 1:
        case 2:
        case 3:
        default:
            assert(false);
    }

    CPNum15_CRn9_COpc0_CRm2:
    switch (instruction.CP) {
        case 0:
        default:
            assert(false);
    }

    CPNum15_CRn9_COpc0_CRm8:
    switch (instruction.CP) {
        case 0:
        default:
            assert(false);
    }

    CPNum15_CRn10_COpc0_CRm0:
    switch (instruction.CP) {
        case 0:
        default:
            assert(false);
    }

    CPNum15_CRn10_COpc0_CRm2:
    switch (instruction.CP) {
        case 0:
        case 1:
        default:
            assert(false);
    }

    CPNum15_CRn11_COpc0_CRm0:
    switch (instruction.CP) {
        default:
            assert(false);
    }

    CPNum15_CRn11_COpc0_CRm1:
    switch (instruction.CP) {
        case 0:
        default:
            assert(false);
    }

    CPNum15_CRn11_COpc0_CRm2:
    switch (instruction.CP) {
        case 0:
        default:
            assert(false);
    }

    CPNum15_CRn11_COpc0_CRm3:
    switch (instruction.CP) {
        default:
            assert(false);
    }
    CPNum15_CRn11_COpc0_CRm4:
    switch (instruction.CP) {
        case 0:
        default:
            assert(false);
    }
    CPNum15_CRn11_COpc0_CRm5:
    switch (instruction.CP) {
        case 0:
        default:
            assert(false);
    }
    CPNum15_CRn11_COpc0_CRm6:
    switch (instruction.CP) {
        case 0:
        default:
            assert(false);
    }
    CPNum15_CRn11_COpc0_CRm7:
    switch (instruction.CP) {
        case 0:
        default:
            assert(false);
    }
    CPNum15_CRn11_COpc0_CRm8:
    switch (instruction.CP) {
        case 0:
        default:
            assert(false);
    }
    CPNum15_CRn11_COpc0_CRm15:
    switch (instruction.CP) {
        case 0:
        default:
            assert(false);
    }
    CPNum15_CRn12_COpc0_CRm0:
    switch (instruction.CP) {
        case 0:
        case 1:
        default:
            assert(false);
    }
    CPNum15_CRn12_COpc0_CRm1:
    switch (instruction.CP) {
        case 0:
        default:
            assert(false);
    }

    CPNum15_CRn13_COpc0_CRm0:
    switch (instruction.CP) {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        default:
            assert(false);
    }

    CPNum15_CRn15_COpc0_CRm2:
    switch (instruction.CP) {
        case 4:
        default:
            assert(false);
    }
    CPNum15_CRn15_COpc0_CRm9:
    switch (instruction.CP) {
        case 0:
        default:
            assert(false);
    }
    CPNum15_CRn15_COpc0_CRm12:
    switch (instruction.CP) {
        case 0:
        case 1:
        case 3:
        default:
            assert(false);
    }
    CPNum15_CRn15_COpc0_CRm13:
    switch (instruction.CP) {
        default:
            assert(false);
    }
    CPNum15_CRn15_COpc0_CRm14:
    switch (instruction.CP) {
        case 0:
        default:
            assert(false);
    }

    CPNum15_CRn15_COpc1_CRm13:
    switch (instruction.CP) {
        default:
            assert(false);
    }

    CPNum15_CRn15_COpc2_CRm13:
    switch (instruction.CP) {
        default:
            assert(false);
    }
    CPNum15_CRn15_COpc3_CRm8:
    switch (instruction.CP) {
        default:
            assert(false);
    }
    CPNum15_CRn15_COpc3_CRm12:
    switch (instruction.CP) {
        default:
            assert(false);
    }
    CPNum15_CRn15_COpc3_CRm13:
    switch (instruction.CP) {
        default:
            assert(false);
    }
    CPNum15_CRn15_COpc4_CRm13:
    switch (instruction.CP) {
        default:
            assert(false);
    }
    CPNum15_CRn15_COpc5_CRm4:
    switch (instruction.CP) {
        case 2:
        default:
            assert(false);
    }
    CPNum15_CRn15_COpc5_CRm5:
    switch (instruction.CP) {
        case 2:
        default:
            assert(false);
    }
    CPNum15_CRn15_COpc5_CRm6:
    switch (instruction.CP) {
        case 2:
        default:
            assert(false);
    }
    CPNum15_CRn15_COpc5_CRm7:
    switch (instruction.CP) {
        case 2:
        default:
            assert(false);
    }
    CPNum15_CRn15_COpc5_CRm13:
    switch (instruction.CP) {
        case 2:
        default:
            assert(false);
    }

    CPNum15_CRn15_COpc6_CRm13:
    switch (instruction.CP) {
        default:
            assert(false);
    }
    CPNum15_CRn15_COpc7_CRm13:
    switch (instruction.CP) {
        default:
            assert(false);
    }




}