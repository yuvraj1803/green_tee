#include <smc/smccc.h>
#include <stdint.h>

void arm_smccc_call(struct arm_smccc_call_params* params, struct arm_smccc_call_return* ret){

    uint64_t function_id = 0;

    if(params->fast_call) function_id |= ARM_SMCCC_FAST_CALL_MASK;
    if(params->smc64) function_id |= ARM_SMCCC_SMC64_MASK;

    // at the moment we only service TOS calls.
    if(params->service_call < 50 || params->service_call > 63){
        ret->call_failed = 1;
        return;
    }

    function_id |= (params->service_call << ARM_SMCCC_OWNER_SHIFT) & ARM_SMCCC_OWNER_MASK;
    function_id |= (params->function_number & ARM_SMCCC_FUNCTION_NR_MASK);

    __arm_smccc_call(function_id, params->args, ret);

}

