#include <smc/green_tee_smc.h>
#include <lib/memory.h>
#include <kernel/panic.h>
#include <lib/stdio.h>
#include <smc/smccc.h>
#include <mm/mmu.h>
#include <mm/mm.h>
#include <crypto/otp.h>
#include <kernel/exceptions.h>

extern uint64_t __green_tee_smc_handler;


void green_tee_smc_pm_ack(){
	struct arm_smccc_call_params params;
	struct arm_smccc_call_return ret;

	params.fast_call = 1;
	params.smc64 = 1;
	params.service_call = ARM_SMCCC_TOS_OEN_MIN;
	params.function_number = GREEN_TEE_SMC_PM_ACK;
	
	LOG("SMC PM ACK: Secondary CPU switching to Normal World\n");

	arm_smccc_call(&params, &ret);

	if(ret.call_failed){
		panic("Green TEE Entry Done SMC Failed.\n");
	}
}

void green_tee_smc_handled(){
	struct arm_smccc_call_params params;
	struct arm_smccc_call_return ret;

	params.fast_call = 1;
	params.smc64 = 1;
	params.service_call = ARM_SMCCC_TOS_OEN_MIN;
	params.function_number = GREEN_TEE_SMC_HANDLED;
	
	LOG("Sending SMC ACK to SPD\n");

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
	
	LOG("Sending SMC NACK to SPD\n");

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
				LOG("GREEN_TEE_LINUX_PRINT Failed\n");
				goto green_tee_smc_fail;
			}

			char* str = (char*) x1;
			LOG("String from NS-EL0: %s\n", str);

			LOG("GREEN_TEE_SMC_LINUX_PRINT SMC Handled\n");

			break;

		case GREEN_TEE_SMC_LINUX_ENCRYPT:
			// x1: base address of 4096 byte block sent from NS-EL0
			mmu_disable();
			ret = mmu_map_range(x1 & ~(PAGE_SIZE-1), x1 & ~(PAGE_SIZE - 1), x1 + (PAGE_SIZE - x1%PAGE_SIZE), PT_ATTR1_NORMAL | PT_SECURE | PT_AP_UNPRIVILEGED_NA_PRIVILEGED_RW | PT_UXN | PT_PXN | PT_AF);
			if(ret < 0){
				LOG("GREEN_TEE_LINUX_ENCRYPT Failed\n");
				goto green_tee_smc_fail;
			}

			str = (char*) x1;
			otp_enc_buffer((uint64_t*) str, 4096);

			mmu_enable();

			LOG("GREEN_TEE_SMC_LINUX_ENCRYPT SMC Handled\n");

			break;
		
		case GREEN_TEE_SMC_LINUX_DECRYPT:

			// x1: base address of 4096 byte block sent from NS-EL0

			mmu_disable();
			ret = mmu_map_range(x1 & ~(PAGE_SIZE-1), x1 & ~(PAGE_SIZE - 1), x1 + (PAGE_SIZE - x1%PAGE_SIZE), PT_ATTR1_NORMAL | PT_SECURE | PT_AP_UNPRIVILEGED_NA_PRIVILEGED_RW | PT_UXN | PT_PXN | PT_AF);
			if(ret < 0){
				LOG("GREEN_TEE_LINUX_DECRYPT Failed\n");
				goto green_tee_smc_fail;
			}
			mmu_invalidate_tlb();
			str = (char*) x1;
			otp_dec_buffer((uint64_t*) str, 4096);
			mmu_enable();
			break;

			LOG("GREEN_TEE_LINUX_DECRYPT SMC Handled\n");

		default:
			LOG("SMC Failed To Handle\n", smc_fid);
			goto green_tee_smc_fail;
	}


	green_tee_smc_handled();

green_tee_smc_fail:
	green_tee_smc_failed();
}

void green_tee_smc_entry_done(green_tee_vector_table_t* vector_table){
    struct arm_smccc_call_params params;
	struct arm_smccc_call_return ret;

	params.fast_call = 1;
	params.smc64 = 1;
	params.service_call = ARM_SMCCC_TOS_OEN_MIN;
	params.function_number = GREEN_TEE_SMC_ENTRY_DONE;
    memset(params.args, 0, sizeof(params.args));
	params.args[1] = (uint64_t) vector_table;

	LOG("Green TEE Entry Done. Returning to SPD for normal world boot.\n");


	arm_smccc_call(&params, &ret);

	if(ret.call_failed){
		panic("Green TEE Entry Done SMC Failed.\n");
	}


}
