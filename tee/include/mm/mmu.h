#ifndef __MMU_H__
#define __MMU_H__

#include <stdint.h>

void mmu_disable();
void mmu_init(void);
int  mmu_map_device(uint64_t base, uint64_t size);
void mmu_enable();
void mmu_invalidate_tlb();
void mmu_load_ttbr0_el1(uint64_t ttbr);
void mmu_load_mair_el1(uint64_t mair);
void mmu_load_tcr_el1(uint64_t tcr);


#define PT_BLOCK                                     (0b01)
#define PT_TABLE                                     (0b11)
#define PT_ATTR0_DEVICE                                     (0b0 << 2)  // MAIR Attribute 0 for device regions (nGnRnE)
#define PT_ATTR1_NORMAL                                     (0b1 << 2)  // MAIR Attribute 1 for normal memory
#define PT_SECURE                                    (0b0 << 5)
#define PT_AP_UNPRIVILEGED_NA_PRIVILEGED_RO          (0b10 << 6)
#define PT_AP_UNPRIVILEGED_NA_PRIVILEGED_RW          (0b00 << 6)
#define PT_AF                                        (1 << 10)
#define PT_UXN                                       (1ULL << 54)
#define PT_PXN                                       (1ULL << 53)

#endif
