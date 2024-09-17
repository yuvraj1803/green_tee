#include <kernel/sync.h>
#include <stdint.h>
#include <kernel/exceptions.h>
#include <lib/stdio.h>
#include <kernel/panic.h>


void __handle_unsupported_exception(uint64_t esr_el1, uint64_t far_el1, uint64_t exception_type){
    printf("[PANIC]: Unsupported Exception Occurred. \n ESR_EL1: %x\n FAR_EL1: %x\n", esr_el1, far_el1);
    halt();
}

void handle_sync(uint64_t esr_el1, uint64_t far_el1, uint64_t exception_type){

}

