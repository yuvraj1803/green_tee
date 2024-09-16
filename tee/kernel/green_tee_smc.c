#include <smc/green_tee_smc.h>
#include <lib/memory.h>
#include <kernel/panic.h>
#include <lib/stdio.h>
#include <smc/smccc.h>
#include <mm/mmu.h>
#include <mm/mm.h>

extern uint64_t vector_table;
extern uint64_t __green_tee_smc_handler;


static void green_tee_smc_handled(){
	struct arm_smccc_call_params params;
	struct arm_smccc_call_return ret;

	params.fast_call = 1;
	params.smc64 = 1;
	params.service_call = ARM_SMCCC_TOS_OEN_MIN;
	params.function_number = GREEN_TEE_SMC_HANDLED;

	arm_smccc_call(&params, &ret);

	if(ret.call_failed){
		panic("Green TEE Entry Done SMC Failed.\n");
	}
}

static void green_tee_smc_failed(){
	struct arm_smccc_call_params params;
	struct arm_smccc_call_return ret;

	params.fast_call = 1;
	params.smc64 = 1;
	params.service_call = ARM_SMCCC_TOS_OEN_MIN;
	params.function_number = GREEN_TEE_SMC_FAILED;

	arm_smccc_call(&params, &ret);

	if(ret.call_failed){
		panic("Green TEE Entry Done SMC Failed.\n");
	}
}

void green_tee_smc_handler(uint64_t smc_fid, uint64_t x1, uint64_t x2, uint64_t x3, uint64_t x4){

	int ret = 0;

	switch(smc_fid & ARM_SMCCC_FUNCTION_NR_MASK){

		case GREEN_TEE_SMC_LINUX_PRINT:
			// x1: physical address of struct print_data sent from normal-world (Linux Kernel)


			ret = mmu_map_range(x1 & ~(PAGE_SIZE-1), x1 & ~(PAGE_SIZE - 1), x1 + (PAGE_SIZE - x1%PAGE_SIZE), PT_ATTR1_NORMAL | PT_SECURE | PT_AP_UNPRIVILEGED_NA_PRIVILEGED_RW | PT_UXN | PT_PXN | PT_AF);
			if(ret < 0){
				LOG("GREEN_TEE_LINUX_PRINT Failed\n", smc_fid);
				goto green_tee_smc_fail;
			}

			char* str = (char*) x1;
			printf("%s\n", str);

			break;

		default:
			LOG("SMC Failed To Handle\n", smc_fid);
			goto green_tee_smc_fail;
	}


	green_tee_smc_handled();

green_tee_smc_fail:
	green_tee_smc_failed();
}

void green_tee_smc_entry_done(){
    struct arm_smccc_call_params params;
	struct arm_smccc_call_return ret;

	params.fast_call = 1;
	params.smc64 = 1;
	params.service_call = ARM_SMCCC_TOS_OEN_MIN;
	params.function_number = GREEN_TEE_SMC_ENTRY_DONE;
    memset(params.args, 0, sizeof(params.args));
	params.args[1] = (uint64_t) &vector_table;
	params.args[2] = (uint64_t) &__green_tee_smc_handler;

	arm_smccc_call(&params, &ret);

	if(ret.call_failed){
		panic("Green TEE Entry Done SMC Failed.\n");
	}

}
