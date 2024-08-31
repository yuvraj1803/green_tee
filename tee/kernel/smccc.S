.section ".text.asm"

.globl __arm_smccc_call
__arm_smccc_call:
// x0: function ID
// x1: base address of arm_smccc_call_params:args[7]
// x2: base address of arm_smccc_call_return
    mov x8, x1
    mov x9, x2

    // load args into hardware registers from args[]
    ldr x1, [x8, #8*1]
    ldr x2, [x8, #8*2]
    ldr x3, [x8, #8*3]
    ldr x4, [x8, #8*4]
    ldr x5, [x8, #8*5]
    ldr x6, [x8, #8*6]
    ldr x7, [x8, #8*7]

    sub sp, sp, 8
    str x9, [sp]

    smc #0

    // bring back arm_smccc_call_return structure's addres from stack
    mov x19, x0
    ldr x0, [sp]
    add sp, sp, 8

    // load return values back to structure
    ldr x1, [x0, #8*1]
    ldr x2, [x0, #8*2]
    ldr x3, [x0, #8*3]
    ldr x4, [x0, #8*4]
    ldr x5, [x0, #8*5]
    ldr x6, [x0, #8*6]
    ldr x7, [x0, #8*7]
    ldr x8, [x0, #8*8]
    ldr x9, [x0, #8*9]
    ldr x10, [x0, #8*10]
    ldr x11, [x0, #8*11]
    ldr x12, [x0, #8*12]
    ldr x13, [x0, #8*13]
    ldr x14, [x0, #8*14]
    ldr x15, [x0, #8*15]
    ldr x16, [x0, #8*16]
    ldr x17, [x0, #8*17]
    ldr x18, [x0, #8*18]
    ldr x0, [x0, #8*0]

    ret
