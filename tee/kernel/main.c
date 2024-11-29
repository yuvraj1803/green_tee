#include <drivers/pl011.h>
#include <lib/stdio.h>
#include <mm/mm.h>
#include <mm/mmu.h>
#include <smc/green_tee_smc.h>
#include <kernel/generic_timer.h>
#include <kernel/interrupts.h>
#include <kernel/exceptions.h>
#include <kernel/pm.h>
#include <crypto/otp.h>

// main() for secondary CPU entry
void secondary_main(void){
	LOG("Booting Secondary CPU\n");
	mmu_secondary_init();
	return;
}

void main(void){
	
	mm_heap_init();
	pl011_init();
	mmu_init();
	generic_timer_init();
	otp_init();

	green_tee_vector_table_t vector_table = {
		.cpu_off_entry = 		(uint64_t)pm_cpu_off_entry,
		.cpu_on_entry = 		(uint64_t)pm_cpu_on_entry,
		.cpu_resume_entry = 	(uint64_t)pm_cpu_resume_entry,
		.cpu_suspend_entry = 	(uint64_t)pm_cpu_suspend_entry,
		.fast_smc_entry = 		(uint64_t)green_tee_smc_handler,
		.fiq_entry = 			0,
		.system_off_entry = 	(uint64_t)pm_cpu_system_off_entry,
		.system_reset_entry = 	(uint64_t)pm_cpu_system_reset_entry,
		.yield_smc_entry = 		(uint64_t)green_tee_smc_handler
	};

	green_tee_smc_entry_done(&vector_table);	// notify trusted secure payload

	while(1);
}
