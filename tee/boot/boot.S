#include "kernel/sysregs.h"
#include "kernel/config.h"
#include "kernel/misc.h"

.section ".text.asm"

.globl _start
_start:

	bl setup_stack	
	bl clear_bss
	bl setup_vector_table

	bl main
	b .

.macro get_cpu_id_macro
    mrs x0, mpidr_el1
    and x1,x0,0xff
    and x0,x0,0xff00
    add x0,x1,x0, lsr #4
.endm

.globl get_cpu_id
get_cpu_id:
    mrs x0, mpidr_el1
    and x1,x0,0xff
    and x0,x0,0xff00
    add x0,x1,x0, lsr #4
    ret

.globl setup_stack
setup_stack:
	get_cpu_id_macro		// CPU ID is in X0   (using a macro because, to 'bl get_cpu_id', I will have to save LR into stack.
							// 									but stack has not been setup yet, so we lose ref of LR ;).
	ldr x1,= __tee_stack_base
	
	lsl x0,x0, #TEE_PER_CPU_STACK_SIZE_SHIFT
	sub x1,x1,x0

	mov sp, x1
	ret

clear_bss:
	ldr x0, =__bss_begin
	ldr x1, =__bss_end
	ldr x2, =0
1:	
	str w2, [x0]
	add x0,x0,4
	cmp x0,x1
	bne 1b
	ret

.globl setup_vector_table
setup_vector_table:
	adr x0, vector_table
	msr vbar_el1, x0
	isb
	ret

.globl halt
halt:
	wfe
	b halt
