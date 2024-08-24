.section ".text.boot"

.globl _start
_start:

	bl setup_stack	
	bl clear_bss
	bl setup_mmu

	bl main
	b .

setup_stack:
	ldr x0, =__tee_limit
	mov sp, x0
	ret

clear_bss:
	ldr x0, =__bss_begin
	ldr x1, =__bss_end
	ldr x2, =0
1:	
	str x2, [x0]
	add x0,x0,1
	cmp x0,x1
	bne 1b
	ret

setup_mmu:
	ret

