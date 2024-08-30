#include <kernel/sync.h>
#include <stdint.h>
#include <kernel/exceptions.h>
#include <lib/stdio.h>

void handle_sync(uint64_t esr_el1, uint64_t far_el1, uint64_t exception_type){
    LOG("SYNC\n");
}

