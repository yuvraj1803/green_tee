#ifndef __IO_H__
#define __IO_H__

#include <stdint.h>

void io_write(uint64_t address, uint64_t val);
uint64_t io_read(uint64_t address);

#endif
