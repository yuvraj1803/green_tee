#include "green_teed.h"
#include <common/runtime_svc.h>
#include <common/debug.h>
#include <bl31/bl31.h>
#include <plat/common/platform.h>
#include <arch_helpers.h>
#include <arch.h>
#include <lib/el3_runtime/context_mgmt.h>
#include <context.h>

#include <stdint.h>



green_teed_cpu_context_t cpu_context_data[PLATFORM_CORE_COUNT];

int32_t green_teed_synchronous_sp_entry(green_teed_cpu_context_t* context){
	cm_el1_sysregs_context_restore(SECURE);
	cm_set_next_eret_context(SECURE);

	uint64_t ret = green_teed_enter_sp(&context->cpu_context);

	return (int32_t) ret;

}

int32_t green_teed_init(void){
	
	int my_cpu = plat_my_core_pos();
	green_teed_cpu_context_t* my_context = &cpu_context_data[my_cpu];

	if(!my_context) goto green_teed_init_fail;

	entry_point_info_t* ep_info = bl31_plat_get_next_image_ep_info(SECURE);
	if(!ep_info) goto green_teed_init_fail;

	cm_init_my_context(ep_info);

	return green_teed_synchronous_sp_entry(my_context);

green_teed_init_fail:
	return 1;

}

int32_t green_teed_setup(void){

	entry_point_info_t* ep_info = bl31_plat_get_next_image_ep_info(SECURE);
	if(!ep_info){
		WARN("Green TEE Entry Point Information Unavailable. SMC will always return SMC_UKN\n");
		goto setup_fail;
	}

	if(!ep_info->pc){
		WARN("Green TEE Entry Point Invalid\n");
		goto setup_fail;
	}

	if(read_sctlr_el3() & SCTLR_EE_BIT){ // not supporting big endian images for now.
		goto setup_fail;
	}	

	int cpu = plat_my_core_pos();
	cm_set_context(&cpu_context_data[cpu], SECURE);
	cpu_context_data[cpu].mpidr_el1 = read_mpidr_el1();
	SET_PARAM_HEAD(ep_info, PARAM_EP, VERSION_1, EP_SECURE | EP_EE_LITTLE | EP_ST_ENABLE);
	ep_info->spsr = SPSR_64(MODE_EL1, MODE_SP_ELX, DISABLE_ALL_EXCEPTIONS);


	bl31_register_bl32_init(&green_teed_init);

	return 0;

setup_fail:
	return 1;
}

uintptr_t green_teed_smc_handler(uint32_t smc_fid, u_register_t x1, u_register_t x2, u_register_t x3, u_register_t x4, void* cookie, void* handle, u_register_t flags){
	

	return 0;

}

DECLARE_RT_SVC(green_teed_rt_svc,
		OEN_TOS_START,
		OEN_TOS_END,
		SMC_TYPE_FAST,
		green_teed_setup,
		green_teed_smc_handler);
