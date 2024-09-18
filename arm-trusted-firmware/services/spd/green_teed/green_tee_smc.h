#ifndef __GREEN_TEE_SMC_H__
#define __GREEN_TEE_SMC_H__

#define ARM_SMCCC_FAST_CALL_MASK    (0x80000000)
#define ARM_SMCCC_YEILD_CALL_MASK   (0x0)

#define ARM_SMCCC_SMC64_MASK        (0x40000000)
#define ARM_SMCCC_SMC32_MASK        (0x0)

#define ARM_SMCCC_OWNER_MASK     (0x3F000000)
#define ARM_SMCCC_OWNER_SHIFT    (24)

#define ARM_SMCCC_FUNCTION_NR_MASK  (0xFFFF)

#define ARM_SMCCC_TOS_OEN_MIN       (50)
#define ARM_SMCCC_TOS_OEN_MAX       (63)

#define ARM_SMCCC_IS_FAST_CALL(function_id)		(function_id & ARM_SMCCC_FAST_CALL_MASK)
#define ARM_SMCCC_IS_YEILD_CALL_MASK(function_id)	(!ARM_SMCCC_IS_FAST_CALL(function_id))

#define ARM_SMCCC_IS_SMC64(function_id)			(function_id & ARM_SMCCC_IS_SMC64)
#define ARM_SMCCC_IS_SMC32(function_id)			(!(ARM_SMCCC_IS_SMC64(function_id)))

#define ARM_SMCCC_OWNER(function_id)	((function_id >> ARM_SMCCC_OWNER_SHIFT) & ARM_SMCCC_OWNER_MASK))


#define GREEN_TEE_SMC_ENTRY_DONE	0
#define GREEN_TEE_SMC_HANDLED		1
#define GREEN_TEE_SMC_FAILED		2
#define GREEN_TEE_SMC_LINUX_INIT	128
#define GREEN_TEE_SMC_LINUX_PRINT	129
#define GREEN_TEE_SMC_LINUX_ENCRYPT 130
#define GREEN_TEE_SMC_LINUX_DECRYPT 131


#endif
