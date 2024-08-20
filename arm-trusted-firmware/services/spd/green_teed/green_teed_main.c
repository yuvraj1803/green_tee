#include "green_teed.h"
#include <common/runtime_svc.h>
#include <common/debug.h>
#include <bl31/bl31.h>
#include <plat/common/platform.h>

#include <stdint.h>

int32_t green_teed_init(void){
	
	INFO("green_teed_init()\n");
	return 1;

}

int32_t green_teed_setup(void){

	entry_point_info_t* ep_info = bl31_plat_get_next_image_ep_info(SECURE);
	if(!ep_info){
		WARN("Green TEE Entry Point Information Unavailable. SMC will always return SMC_UKN\n");
		return 1;
	}

	if(!ep_info->pc){
		WARN("Green TEE Entry Point Invalid\n");
		return 1;
	}	

	

	bl31_register_bl32_init(&green_teed_init);

	return 0;
}

uintptr_t green_teed_smc_handler(uint32_t smc_fid, u_register_t x1, u_register_t x2, u_register_t x3, u_register_t x4, void* cookie, void* handle, u_register_t flags){
	

	return 0;

}

DECLARE_RT_SVC(green_teed_rt_svc,
		OEN_STD_START,
		OEN_STD_END,
		SMC_TYPE_FAST,
		green_teed_setup,
		green_teed_smc_handler);
