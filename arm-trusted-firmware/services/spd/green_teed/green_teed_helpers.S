#include "green_teed.h"
#include <asm_macros.S>

.global green_teed_enter_sp

green_teed_enter_sp:
    sub sp, sp, #GREEN_TEED_SP_CONTEXT_SIZE
    stp x19, x20, [sp, #GREEN_TEED_SP_CONTEXT_X19]
    stp x21, x22, [sp, #GREEN_TEED_SP_CONTEXT_X21]
    stp x23, x24, [sp, #GREEN_TEED_SP_CONTEXT_X23]
    stp x25, x26, [sp, #GREEN_TEED_SP_CONTEXT_X25]
    stp x27, x28, [sp, #GREEN_TEED_SP_CONTEXT_X27]
    stp x29, x30, [sp, #GREEN_TEED_SP_CONTEXT_X29]

    b el3_exit

.globl green_teed_enter_sp
green_teed_exit_sp:

    ldp x19, x20, [sp, #GREEN_TEED_SP_CONTEXT_X19]
    ldp x21, x22, [sp, #GREEN_TEED_SP_CONTEXT_X21]
    ldp x23, x24, [sp, #GREEN_TEED_SP_CONTEXT_X23]
    ldp x25, x26, [sp, #GREEN_TEED_SP_CONTEXT_X25]
    ldp x27, x28, [sp, #GREEN_TEED_SP_CONTEXT_X27]
    ldp x29, x30, [sp, #GREEN_TEED_SP_CONTEXT_X29]

    add sp, sp, #GREEN_TEED_SP_CONTEXT_SIZE
    ret
