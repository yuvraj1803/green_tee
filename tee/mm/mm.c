#include <mm/mm.h>
#include <lib/stdio.h>
#include <kernel/errno.h>
#include <kernel/panic.h>

#define MM_HEAP_PAGE_TAKEN 	0b1000
#define MM_HEAP_PAGE_FREE  	0b0000
#define MM_HEAP_PAGE_FIRST 	0b0010
#define MM_HEAP_PAGE_HAS_NEXT	0b0100

const uint64_t heap_size_pages = (MM_HEAP_END - MM_HEAP_BEGIN) / PAGE_SIZE;

uint8_t heap_metadata[(MM_HEAP_END - MM_HEAP_BEGIN) / PAGE_SIZE];

extern uint64_t __tee_end;

void mm_heap_init(void){

	if(__tee_end > MM_HEAP_END) panic("TEE image overlapping heap region. Reduce heap size or stack size.\n");

	for(int page = 0; page < heap_size_pages; page++) heap_metadata[page] = MM_HEAP_PAGE_FREE;

	LOG("Heap Initialised: %x - %x (size: %x)\n", MM_HEAP_BEGIN, MM_HEAP_END, MM_HEAP_SIZE);

}

int64_t mm_find_free_page_block(uint64_t size){
	
	if(size & (PAGE_SIZE - 1)) return 0;
	
	uint64_t num_pages = size / PAGE_SIZE;
	if(num_pages > (MM_HEAP_END - MM_HEAP_BEGIN)/PAGE_SIZE) return -EMALLOC; // requested memory exceeds heap size

	for(int page=0; page < heap_size_pages; ){

		int block_found = 1;

		for(int _page = page; _page < page + num_pages; _page++){
			if(heap_metadata[_page] != MM_HEAP_PAGE_FREE){
				page = _page+1;
				block_found = 0;
				break;
			}
		}
		if(block_found){
			for(int _page = page; _page < page + num_pages; _page++) {
				if(_page == page) heap_metadata[_page] = MM_HEAP_PAGE_FIRST | MM_HEAP_PAGE_TAKEN;
				else if(_page == page + num_pages - 1) heap_metadata[_page] = MM_HEAP_PAGE_TAKEN;
				else{
					heap_metadata[_page] = MM_HEAP_PAGE_TAKEN | MM_HEAP_PAGE_HAS_NEXT;
				}
			}
			if(num_pages > 1) heap_metadata[page] |= MM_HEAP_PAGE_HAS_NEXT;
			return page;
		}

	}

	return -EMALLOC; // no free blocks found
}

void* malloc(uint64_t size){
	
	size = size + (PAGE_SIZE - size % PAGE_SIZE); // align given size to PAGE_SIZE
	
	int64_t free_page_block = mm_find_free_page_block(size);
	if(free_page_block == -EMALLOC) goto malloc_fail;

	return (void*)(MM_HEAP_BEGIN + free_page_block * PAGE_SIZE); 

malloc_fail:
	return (void*)0;
}

void mm_free_block(uint64_t addr){
	
	uint64_t start_page = (addr - MM_HEAP_BEGIN) / PAGE_SIZE;
	
	for(int page = start_page;;page++){
		if(heap_metadata[page] == MM_HEAP_PAGE_FREE) return;

		heap_metadata[page] = MM_HEAP_PAGE_FREE;
		if(!(heap_metadata[page] & MM_HEAP_PAGE_HAS_NEXT)) return;
	}

}

void free(void* base){
	
	uint64_t addr = (uint64_t)base;
	
	addr = addr - addr%PAGE_SIZE; // Align lower with page size.

	mm_free_block(addr);

}
