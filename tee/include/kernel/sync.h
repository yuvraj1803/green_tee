#ifndef __SYNC_H__
#define __SYNC_H__

#include <stdint.h>
#include <kernel/exceptions.h>

void handle_sync(uint64_t esr_el1, uint64_t far_el1, uint64_t exception_type);
void __handle_unsupported_exception(uint64_t esr_el1, uint64_t far_el1, uint64_t exception_type);

#endif
