#include "green_teed.h"
#include <common/runtime_svc.h>
#include <common/debug.h>

#include <stdint.h>

int32_t green_teed_setup(void){
	INFO("GREEN TEED SETUP!");
	return 0;
}

uintptr_t green_teed_svc_handler(uint32_t smc_fid, u_register_t x1, u_register_t x2, u_register_t x3, u_register_t x4, void* cookie, void* handle, u_register_t flags){
	

	return 0;

}

DECLARE_RT_SVC(green_teed_rt_svc,
		OEN_STD_START,
		OEN_STD_END,
		SMC_TYPE_FAST,
		green_teed_setup,
		green_teed_svc_handler);
