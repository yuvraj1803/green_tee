.section ".text.asm"

.globl otp_get_key
otp_get_key:
// aarch64-linux-gnu-gcc assembler throws an error when using RNDR register. I am going with system counter value as the random key.
	mrs x0, cntpct_el0
	ret