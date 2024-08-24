#include <linux/green_tee/green_tee.h>
#include <linux/printk.h>
#include <linux/errno.h>
#include <linux/arm-smccc.h>

#include <asm/alternative-macros.h>

int green_tee_arch_init(void){

    struct arm_smccc_res res;
    arm_smccc_1_1_smc(ARM_SMCCC_CALL_VAL(ARM_SMCCC_FAST_CALL, ARM_SMCCC_SMC_64, ARM_SMCCC_OWNER_TRUSTED_OS, 0x0)
        ,0,0,0,0,0,0,0);

    return 0;

green_tee_arch_init_fail:
    return -EFAULT;
}
