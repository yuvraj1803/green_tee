#ifndef __SMC_H__
#define __SMC_H__

#include <stdint.h>

#define ARM_SMCCC_FAST_CALL_MASK    (0x80000000)
#define ARM_SMCCC_YEILD_CALL_MASK   (0x0)

#define ARM_SMCCC_SMC64_MASK        (0x40000000)
#define ARM_SMCCC_SMC32_MASK        (0x0)

#define ARM_SMCCC_OWNER_MASK     (0x3F000000)
#define ARM_SMCCC_OWNER_SHIFT    (24)

#define ARM_SMCCC_FUNCTION_NR_MASK  (0xFFFF)

#define ARM_SMCCC_TOS_OEN_MIN       (50)
#define ARM_SMCCC_TOS_OEN_MAX       (63)


struct arm_smccc_call_params{
        uint8_t     fast_call;
        uint8_t     smc64;
        uint8_t     service_call;
        uint16_t    function_number;
        uint64_t    args[7]; // arguments passed from x1-x7
};

struct arm_smccc_call_return{
        uint64_t regs[18]; // returns values in registers x0 - x17
        uint8_t call_failed;
};


void __arm_smccc_call(uint64_t function_id, uint64_t args[], struct arm_smccc_call_return* ret);
void arm_smccc_call(struct arm_smccc_call_params* params, struct arm_smccc_call_return* ret);

#endif
