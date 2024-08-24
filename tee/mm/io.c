#include <mm/io.h>
#include <stdint.h>

void io_write(uint64_t address, uint64_t val){
	*(uint64_t*)address = val;
}

uint64_t io_read(uint64_t address){
	return *(uint64_t*) address;
}
