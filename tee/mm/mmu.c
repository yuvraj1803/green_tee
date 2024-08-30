#include <mm/mmu.h>
#include <kernel/errno.h>
#include <mm/mm.h>
#include <stdint.h>
#include <kernel/panic.h>
#include <kernel/sysregs.h>
#include <lib/stdio.h>


extern uint64_t __tee_asm_text_begin;
extern uint64_t	__tee_asm_text_end;

extern uint64_t	__tee_text_begin;
extern uint64_t	__tee_text_end;

extern uint64_t	__tee_data_begin;
extern uint64_t	__tee_data_end;

extern uint64_t	__tee_rodata_begin;
extern uint64_t	__tee_rodata_end;

extern uint64_t __bss_begin;
extern uint64_t __bss_end;

extern uint64_t __tee_limit;

uint64_t *l1_table;


int mmu_map_page(uint64_t virt, uint64_t phys, uint64_t flags){
    if(phys & (PAGE_SIZE - 1)) return -EALIGN;
    if(virt & (PAGE_SIZE - 1)) return -EALIGN;

    int l1_index = (virt >> 30) & (512 - 1);
    int l2_index = (virt >> 21) & (512 - 1);


    if(!l1_table) l1_table = malloc(PAGE_SIZE);
    if(!l1_table) goto no_mem;

    if(!l1_table[l1_index]){
        l1_table[l1_index] = (uint64_t)malloc(PAGE_SIZE);

        if(!l1_table[l1_index]) goto no_mem;

        l1_table[l1_index] |= PT_TABLE;
    }


    uint64_t* l2_table = (uint64_t*) (l1_table[l1_index] & ~(PAGE_SIZE - 1));
    if(!l2_table[l2_index]) l2_table[l2_index] = (phys | flags | PT_BLOCK);

    return 0;
no_mem:

    return -ENOMEM;
}

// If mmu_map_range() and mmu_map_device() is called after MMU is turned on
// caller must make sure to disable MMU and invalidate EL1 TLBs after mapping has taken place.


int mmu_map_range(uint64_t virt, uint64_t phys_start, uint64_t phys_end, uint64_t flags){

    if(phys_start & (PAGE_SIZE - 1)) return -EALIGN;
    if(phys_end & (PAGE_SIZE - 1)) return -EALIGN;

    while(phys_start != phys_end){

        int ret = mmu_map_page(virt, phys_start, flags);
        if(ret < 0) return ret;

        phys_start += PAGE_SIZE;
        virt += PAGE_SIZE;
    }


    return 0;

}

int mmu_map_device(uint64_t base, uint64_t size){

    if(base & (PAGE_SIZE - 1)) return -EALIGN;
    if(size & (PAGE_SIZE - 1)) return -EALIGN;

    return mmu_map_range(base, base, base + size, PT_ATTR0_DEVICE | PT_SECURE | PT_AP_UNPRIVILEGED_NA_PRIVILEGED_RW | PT_AF | PT_UXN | PT_PXN);

}


void mmu_init(void){


    mmu_disable();

    int ret = 0;

    // asm code
    ret = mmu_map_range((uint64_t)&__tee_asm_text_begin,(uint64_t)&__tee_asm_text_begin,(uint64_t) &__tee_asm_text_end, PT_ATTR1_NORMAL | PT_SECURE | PT_AP_UNPRIVILEGED_NA_PRIVILEGED_RO | PT_UXN | PT_AF);

    // code
    ret = mmu_map_range((uint64_t)&__tee_text_begin, (uint64_t)&__tee_text_begin, (uint64_t)&__tee_text_end, PT_ATTR1_NORMAL | PT_SECURE | PT_AP_UNPRIVILEGED_NA_PRIVILEGED_RO | PT_UXN | PT_AF);

    //data
    ret = mmu_map_range((uint64_t)&__tee_data_begin, (uint64_t)&__tee_data_begin, (uint64_t)&__tee_data_end, PT_ATTR1_NORMAL | PT_SECURE | PT_AP_UNPRIVILEGED_NA_PRIVILEGED_RW | PT_UXN | PT_PXN | PT_AF);

    // read-only data
    ret = mmu_map_range((uint64_t)&__tee_rodata_begin, (uint64_t)&__tee_rodata_begin, (uint64_t)&__tee_rodata_end, PT_ATTR1_NORMAL | PT_SECURE | PT_AP_UNPRIVILEGED_NA_PRIVILEGED_RO | PT_UXN | PT_PXN | PT_AF);

    // bss
    ret = mmu_map_range((uint64_t)&__bss_begin, (uint64_t)&__bss_begin, (uint64_t)&__bss_end, PT_ATTR1_NORMAL | PT_SECURE | PT_AP_UNPRIVILEGED_NA_PRIVILEGED_RW | PT_UXN | PT_PXN | PT_AF);

    // rest of the memory
    ret = mmu_map_range((uint64_t)&__bss_end, (uint64_t)&__bss_end, (uint64_t)&__tee_limit, PT_ATTR1_NORMAL | PT_SECURE | PT_AP_UNPRIVILEGED_NA_PRIVILEGED_RW | PT_UXN | PT_PXN | PT_AF);


    if(ret < 0) panic("Unable to map TEE code/data for MMU init\n");

    mmu_load_ttbr0_el1((uint64_t) l1_table);
    mmu_load_tcr_el1(TCR_EL1);
    mmu_load_mair_el1(MAIR_EL1);
    mmu_invalidate_tlb();
    mmu_enable();

    LOG("MMU initialised\n");

}
