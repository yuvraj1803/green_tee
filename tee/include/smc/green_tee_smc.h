#ifndef __GREEN_TEE_SMC_H__
#define __GREEN_TEE_SMC_H__

#define GREEN_TEE_SMC_ENTRY_DONE    0
#define GREEN_TEE_SMC_HANDLED		1
#define GREEN_TEE_SMC_FAILED		2
#define GREEN_TEE_SMC_PM_ACK        3
#define GREEN_TEE_SMC_LINUX_INIT	128
#define GREEN_TEE_SMC_LINUX_PRINT	129
#define GREEN_TEE_SMC_LINUX_ENCRYPT 130
#define GREEN_TEE_SMC_LINUX_DECRYPT 131

#ifndef __ASSEMBLER__
#include <smc/smccc.h>
#include <kernel/exceptions.h>

void green_tee_smc_entry_done(green_tee_vector_table_t* vector_table);
void green_tee_smc_handler(uint64_t smc_fid, uint64_t x1, uint64_t x2, uint64_t x3, uint64_t x4);
void green_tee_smc_handled();
void green_tee_smc_pm_ack();
#endif

#endif
