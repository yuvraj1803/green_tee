#include <drivers/pl011.h>
#include <lib/stdio.h>
#include <mm/mm.h>
#include <mm/mmu.h>
#include <smc/green_tee_smc.h>
#include <kernel/generic_timer.h>
#include <kernel/interrupts.h>
#include <crypto/otp.h>
#include <kernel/exceptions.h>

void main(void){
	
	mm_heap_init();
	pl011_init();
	mmu_init();
	generic_timer_init();
	otp_init();

	green_tee_vector_table_t vector_table = {
		.cpu_off_entry = 0,
		.cpu_on_entry = 0,
		.cpu_resume_entry = 0,
		.cpu_suspend_entry = 0,
		.fast_smc_entry = 0,
		.fast_smc_entry = (uint64_t) green_tee_smc_handler,
		.fiq_entry = 0,
		.system_off_entry = 0,
		.system_reset_entry = 0,
		.yield_smc_entry = (uint64_t) green_tee_smc_handler
	};

	green_tee_smc_entry_done(&vector_table);	// notify trusted secure payload

	while(1);
}
