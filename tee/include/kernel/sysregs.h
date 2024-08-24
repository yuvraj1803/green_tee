#ifndef __SYSREGS_H__
#define __SYSREGS_H__

#define BIT(x)	(1U << x)

#define SCTLR_EL1_M	BIT(0)
#define SCTLR_EL1_C	BIT(2)
#define SCTLR_EL1_I	BIT(12)
#define SCTLR_EL1_WXN	BIT(19)

#define SCTLR_EL1_MMU_OFF (SCTLR_EL1_C | SCTLR_EL1_I | SCTLR_EL1_WXN)
#define SCTLR_EL1_MMU_ON (SCTLR_EL1_MMU_OFF | SCTLR_EL1_M)

#ifndef __ASSEMBLER__
#endif /* __ASSEMBLER__ */

#endif /* __SYSREGS_H__ */
