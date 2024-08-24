#ifndef __IO_H__
#define __IO_H__

#include <stdint.h>

void io_write64(uint64_t address, uint64_t val);
void io_write32(uint64_t address, uint32_t val);

uint64_t io_read64(uint64_t address);
uint32_t io_read32(uint64_t address);
#endif
