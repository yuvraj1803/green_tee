#include <drivers/pl011.h>
#include <lib/stdio.h>
#include <mm/mm.h>

void main(void){
	
	pl011_init();
	mm_heap_init();	
	
	while(1);
}
