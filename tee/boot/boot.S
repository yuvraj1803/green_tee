#include "kernel/sysregs.h"

.section ".text.asm"

.globl _start
_start:

	bl setup_stack	
	bl clear_bss
	bl setup_vector_table

	bl main
	b .

setup_stack:
	ldr x0, =__tee_stack_base
	mov sp, x0
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

setup_vector_table:
	adr x0, vector_table
	msr vbar_el1, x0
	isb
	ret

.globl halt
halt:
	wfe
	b halt
