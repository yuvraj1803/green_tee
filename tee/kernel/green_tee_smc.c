#include <smc/green_tee_smc.h>
#include <lib/memory.h>

extern uint64_t vector_table;

void green_tee_smc_entry_done(){
    struct arm_smccc_call_params params;
	struct arm_smccc_call_return ret;

	params.fast_call = 1;
	params.smc64 = 1;
	params.service_call = GREEN_TEE_SMC_ENTRY_DONE;
    memset(params.args, 0, sizeof(params.args));
	params.args[1] = (uint64_t) &vector_table;

	arm_smccc_call(&params, &ret);
}
