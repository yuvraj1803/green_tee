#ifndef __GREEN_TEE_SMC_H__
#define __GREEN_TEE_SMC_H__

#define GREEN_TEE_SMC_ENTRY_DONE    0
#define GREEN_TEE_SMC_HANDLED		1
#define GREEN_TEE_SMC_FAILED		2
#define GREEN_TEE_SMC_LINUX_INIT	128
#define GREEN_TEE_SMC_LINUX_PRINT	129


#include <smc/smccc.h>

void green_tee_smc_entry_done();
void green_tee_smc_handler(uint64_t smc_fid, uint64_t x1, uint64_t x2, uint64_t x3, uint64_t x4);

#endif
