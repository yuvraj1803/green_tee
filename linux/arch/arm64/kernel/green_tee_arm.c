#pragma GCC push_options
#pragma GCC optimize ("O0")

#include <linux/green_tee/green_tee.h>
#include <linux/printk.h>
#include <linux/errno.h>
#include <linux/arm-smccc.h>
#include <linux/green_tee/green_tee_smc.h>

#include <asm/alternative-macros.h>
#include <asm/io.h>
#include <asm/page.h>

int green_tee_arch_print_data(struct green_tee_print_data* print_data){

    struct arm_smccc_res res;
    arm_smccc_1_1_smc(ARM_SMCCC_CALL_VAL(ARM_SMCCC_STD_CALL, ARM_SMCCC_SMC_64, ARM_SMCCC_OWNER_TRUSTED_OS, GREEN_TEE_SMC_LINUX_PRINT)
        ,virt_to_phys(print_data->str),0,0,0,0,0,0, &res);

    if(res.a0 != 0) return -EPERM;
    return 0;

}

int green_tee_arch_encrypt_data(char* buff){
    struct arm_smccc_res res;
    arm_smccc_1_1_smc(ARM_SMCCC_CALL_VAL(ARM_SMCCC_STD_CALL, ARM_SMCCC_SMC_64, ARM_SMCCC_OWNER_TRUSTED_OS, GREEN_TEE_SMC_LINUX_ENCRYPT)
    ,virt_to_phys(buff),0,0,0,0,0,0, &res);

    if(res.a0 != 0) return -EPERM;

    return 0;

}

int green_tee_arch_decrypt_data(char* buff){
    struct arm_smccc_res res;
    arm_smccc_1_1_smc(ARM_SMCCC_CALL_VAL(ARM_SMCCC_STD_CALL, ARM_SMCCC_SMC_64, ARM_SMCCC_OWNER_TRUSTED_OS, GREEN_TEE_SMC_LINUX_DECRYPT)
    ,virt_to_phys(buff),0,0,0,0,0,0, &res);

    if(res.a0 != 0) return -EPERM;

    return 0;
}

int green_tee_arch_init(void){

    struct arm_smccc_res res;
    arm_smccc_1_1_smc(ARM_SMCCC_CALL_VAL(ARM_SMCCC_FAST_CALL, ARM_SMCCC_SMC_64, ARM_SMCCC_OWNER_TRUSTED_OS, GREEN_TEE_SMC_LINUX_INIT)
        ,0,0,0,0,0,0,0, &res);

    return 0;
}

#pragma GCC pop_options