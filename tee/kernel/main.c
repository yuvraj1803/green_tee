#include <drivers/pl011.h>
#include <lib/stdio.h>

void main(void){
	
	pl011_init();
	
	printf("Hello, World\n");

	while(1);
}
