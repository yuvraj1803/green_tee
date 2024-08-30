#include <kernel/exceptions.h>
#include <stdint.h>
#include <kernel/panic.h>
#include <lib/stdio.h>


char* exception_type_string[] = {
    "CURRENT_EL_SP0_SYNC",
    "CURRENT_EL_SP0_IRQ",
    "CURRENT_EL_SP0_FIQ",
    "CURRENT_EL_SP0_SERROR",

    "CURRENT_EL_SPX_SYNC",
    "CURRENT_EL_SPX_IRQ",
    "CURRENT_EL_SPX_FIQ",
    "CURRENT_EL_SPX_SERROR",

    "LOWER_EL_64_SYNC",
    "LOWER_EL_64_IRQ",
    "LOWER_EL_64_FIQ",
    "LOWER_EL_64_SERROR",

    "LOWER_EL_32_SYNC",
    "LOWER_EL_32_IRQ",
    "LOWER_EL_32_FIQ",
    "LOWER_EL_32_SERROR"
};

void __handle_unsupported_exception(uint64_t esr_el1, uint64_t far_el1, uint64_t exception_type){
    LOG("ESR_EL1: %x \n FAR_EL1: %x \n", esr_el1, far_el1);
    LOG("Unsupported Exception Occurred: %s\n", exception_type_string[exception_type]);
    halt();
}

