.section ".text.asm"

.globl io_write32
io_write32:
	str w1, [x0]
	ret

.globl io_write64
io_write64:
	str x1, [x0]
	ret

.globl io_read32
io_read32:		
	ldr w0, [x0]
	ret

.globl io_read64
io_read64:	
	ldr x0, [x0]
	ret
