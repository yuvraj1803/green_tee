#ifndef __MM_H__
#define __MM_H__

#include <stdint.h>


#define KB	(1024)
#define MB	(1024 * KB)
#define GB	(1024 * MB)

#define PAGE_SIZE	(4*KB)

#define MM_STACK_BASE	0xf000000
#define MM_STACK_SIZE	(2*MB)

#define MM_HEAP_SIZE	(8*MB)
#define MM_HEAP_END	(MM_STACK_BASE - MM_STACK_SIZE)
#define MM_HEAP_BEGIN	(MM_HEAP_END - MM_HEAP_SIZE)

void* malloc(uint64_t size);
void free(void* base);
void mm_heap_init();
#endif
