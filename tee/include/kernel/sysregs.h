#ifndef __SYSREGS_H__
#define __SYSREGS_H__

#define BIT(x)	(1U << x)

#define SCTLR_EL1_M	BIT(0)
#define SCTLR_EL1_C	BIT(2)
#define SCTLR_EL1_I	BIT(12)
#define SCTLR_EL1_WXN	BIT(19)
#define SCTLR_EL1_MMU_OFF (SCTLR_EL1_C | SCTLR_EL1_I | SCTLR_EL1_WXN)
#define SCTLR_EL1_MMU_ON (SCTLR_EL1_MMU_OFF | SCTLR_EL1_M)

#define TCR_EL1_T0SZ		    (64-39)
#define TCR_EL1_T0SZ_SHIFT	    (0)
#define TCR_EL1_IRGN0		    (0)	// Normal Memory Inner Non-Cacheable
#define TCR_EL1_IRGN0_SHIFT	    (8)
#define TCR_EL1_ORGN0		    (0)	// Normal Memory Outer Non-Cacheable
#define TCR_EL1_ORGN0_SHIFT	    (10)
#define TCR_EL1_SH0		        (0b10)	// Outer Shareable
#define TCR_EL1_SH0_SHIFT	    (12)
#define TCR_EL1_TG0             (0b00)  // 4KB granule
#define TCR_EL1_TG0_SHIFT       (14)
#define TCR_EL1_A1              (0)     // TTBR0_EL1 defines ASID
#define TCR_EL1_A1_SHIFT        (22)
#define TCR_EL1_IPS             (0b110ULL)     // 48-bit IPS
#define TCR_EL1_IPS_SHIFT       (32)
#define TCR_EL1_AS              (0ULL)     // 8-bit ASID
#define TCR_EL1_AS_SHIFT        (36)
#define TCR_EL1_HA              (1ULL)   // Hardware Access flag enabled
#define TCR_EL1_HA_SHIFT        (39)
#define TCR_EL1                 ((TCR_EL1_T0SZ << TCR_EL1_T0SZ_SHIFT) | \
                                 (TCR_EL1_IRGN0 << TCR_EL1_IRGN0_SHIFT) | \
                                 (TCR_EL1_ORGN0 << TCR_EL1_ORGN0_SHIFT) | \
                                 (TCR_EL1_SH0 << TCR_EL1_SH0_SHIFT) | \
                                 (TCR_EL1_TG0 << TCR_EL1_TG0_SHIFT) | \
                                 (TCR_EL1_A1 << TCR_EL1_A1_SHIFT) | \
                                 (TCR_EL1_IPS << TCR_EL1_IPS_SHIFT) | \
                                 (TCR_EL1_AS << TCR_EL1_AS_SHIFT) \
                                )

#define MAIR_EL1_DEVICE_nGnRnE     (0b00000000)
#define MAIR_EL1_NORMAL            (0b01000100) // Outer Non-Cacheable Inner Non-Cacheable
#define MAIR_EL1_ATTR0             (MAIR_EL1_DEVICE_nGnRnE)
#define MAIR_EL1_ATTR1             (MAIR_EL1_NORMAL)
#define MAIR_EL1                   (MAIR_EL1_ATTR0 | (MAIR_EL1_ATTR1 << 8))

#ifndef __ASSEMBLER__

#endif /* __ASSEMBLER__ */

#endif /* __SYSREGS_H__ */
