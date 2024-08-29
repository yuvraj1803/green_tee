#include <drivers/pl011.h>
#include <lib/stdio.h>
#include <mm/mm.h>
#include <mm/mmu.h>

void main(void){
	

	pl011_init();
	mm_heap_init();	
	mmu_init();
	
	while(1);
}
