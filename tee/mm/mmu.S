#include <kernel/sysregs.h>

.section ".text.asm"

.globl mmu_load_tcr_el1
mmu_load_tcr_el1:
    msr tcr_el1, x0
    isb
    ret

.globl mmu_load_mair_el1
mmu_load_mair_el1:
    msr mair_el1, x0
    isb
    ret

.globl mmu_load_ttbr0_el1
mmu_load_ttbr0_el1:
    msr ttbr0_el1, x0
    isb
    ret

.globl mmu_invalidate_tlb
mmu_invalidate_tlb:
    dsb ish
	tlbi vmalle1
    dsb ish
	isb
	ret

.globl mmu_disable
mmu_disable:
	ldr x0, =SCTLR_EL1_MMU_OFF
	msr sctlr_el1, x0
	isb
	ret

.globl mmu_enable
mmu_enable:
	ldr x0, =SCTLR_EL1_MMU_ON
	msr sctlr_el1, x0
	isb
	ret

.globl mmu_is_enabled
mmu_is_enabled:
    mrs x0, sctlr_el1
    ldr x1, =SCTLR_EL1_M
    and x0, x0, x1
    ret
