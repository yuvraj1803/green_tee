#include <linux/green_tee/green_tee.h>
#include <linux/printk.h>
#include <linux/kernel.h>
#include <linux/errno.h>

int green_tee_init(void){

    int ret;

    ret = green_tee_arch_init();
    if(ret < 0) goto green_tee_init_fail;
    
    return ret;

green_tee_init_fail:
    return -EFAULT;
}

device_initcall(green_tee_init);
