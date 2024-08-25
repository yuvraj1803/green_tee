#include "kernel/sysregs.h"

.section ".text.boot"

.globl _start
_start:

	bl setup_stack	
	bl clear_bss

	bl disable_mmu

	bl setup_mmu

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

disable_mmu:
	ldr x0, =SCTLR_EL1_MMU_OFF
	msr sctlr_el1, x0
	isb
	ret

setup_mmu:
	ret

.globl halt
halt:
	wfe
	b halt
