#include <mm/io.h>
#include <stdint.h>

void io_write64(uint64_t address, uint64_t val){
	*(uint64_t*)address = val;
}

void io_write32(uint64_t address, uint32_t val){
	*(uint64_t*)address = val;
}

uint64_t io_read64(uint64_t address){
	return *(uint64_t*) address;
}

uint32_t io_read32(uint64_t address){
	return (uint32_t)(*(uint64_t*)address);
}
