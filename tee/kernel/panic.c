#include <kernel/panic.h>
#include <lib/stdio.h>


void panic(char* msg){
	printf("[PANIC]: %s\n", msg);
	halt();
}
