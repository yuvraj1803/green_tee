#include <kernel/panic.h>
#include <lib/stdio.h>

void halt();

void panic(char* msg){
	printf("[PANIC]: %s\n", msg);
	halt();
}
