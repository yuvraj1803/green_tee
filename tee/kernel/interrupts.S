.section ".text.asm"

.globl enable_interrupts
enable_interrupts:
    msr daifset, 0b11
    isb
    ret

.globl disable_interrupts
disable_interrupts:
    msr daifclr, 0b11
    isb
    ret
