#include <kernel/exceptions.h>
#include "entry.S"

.section ".text.asm"

.globl __green_tee_smc_handler
__green_tee_smc_handler:
    b green_tee_smc_handler

.macro ventry handler
.align 7 // each handler must be aligned to 2^7 (128) bytes
    b \handler
.endm

.globl vector_table
.align 11   // vector table must be aligned to 2^11 (2048) bytes
vector_table:
    ventry current_el_sp0_sync
    ventry current_el_sp0_irq
    ventry current_el_sp0_fiq
    ventry current_el_sp0_serror

    ventry current_el_spx_sync
    ventry current_el_spx_irq
    ventry current_el_spx_fiq
    ventry current_el_spx_serror

    ventry lower_el_64_sync
    ventry lower_el_64_irq
    ventry lower_el_64_fiq
    ventry lower_el_64_serror

    ventry lower_el_32_sync
    ventry lower_el_32_irq
    ventry lower_el_32_fiq
    ventry lower_el_32_serror

.macro handle_unsupported_exception exception_type
    mrs x0, esr_el1
    mrs x1, far_el1
    mov x2, \exception_type
    bl __handle_unsupported_exception
    b halt                          // we should never come here, but anyway.
.endm


.macro handle_sync_exception exception_type
    kernel_entry
    mrs x0, esr_el1
    mrs x1, far_el1
    mov x2, \exception_type
    bl handle_sync
    kernel_exit
.endm

.macro handle_async_exception exception_type
    kernel_entry
    bl handle_async
    kernel_exit
.endm

current_el_sp0_sync:
    handle_unsupported_exception CURRENT_EL_SP0_SYNC
current_el_sp0_irq:
    handle_unsupported_exception CURRENT_EL_SP0_IRQ
current_el_sp0_fiq:
    handle_unsupported_exception CURRENT_EL_SP0_FIQ
current_el_sp0_serror:
    handle_unsupported_exception CURRENT_EL_SP0_SERROR

current_el_spx_sync:
    handle_unsupported_exception CURRENT_EL_SPX_SYNC
current_el_spx_irq:
    handle_async_exception CURRENT_EL_SPX_IRQ
current_el_spx_fiq:
    handle_async_exception CURRENT_EL_SPX_FIQ
current_el_spx_serror:
    handle_unsupported_exception CURRENT_EL_SPX_SERROR

lower_el_64_sync:
    handle_sync_exception LOWER_EL_64_SYNC
lower_el_64_irq:
    handle_async_exception LOWER_EL_64_IRQ
lower_el_64_fiq:
    handle_async_exception LOWER_EL_64_FIQ
lower_el_64_serror:
    handle_sync_exception LOWER_EL_64_SERROR

lower_el_32_sync:
    handle_unsupported_exception LOWER_EL_32_SYNC
lower_el_32_irq:
    handle_unsupported_exception LOWER_EL_32_IRQ
lower_el_32_fiq:
    handle_unsupported_exception LOWER_EL_32_FIQ
lower_el_32_serror:
    handle_unsupported_exception LOWER_EL_32_SERROR
