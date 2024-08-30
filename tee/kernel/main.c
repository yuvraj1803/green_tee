#include <drivers/pl011.h>
#include <lib/stdio.h>
#include <mm/mm.h>
#include <mm/mmu.h>
#include <smc/green_tee_smc.h>

void main(void){
	

	pl011_init();
	mm_heap_init();	
	mmu_init();
	
	green_tee_smc_entry_done();	// notify trusted secure payload

	while(1);
}
