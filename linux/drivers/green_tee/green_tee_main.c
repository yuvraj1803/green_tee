#include <linux/green_tee/green_tee.h>
#include <linux/printk.h>
#include <linux/kernel.h>
#include <linux/errno.h>
#include <linux/fs.h>
#include <linux/miscdevice.h>

static int green_tee_dev_initialised = 0;

static long green_tee_ioctl(struct file* file, unsigned int ioctl, unsigned long arg){
    return 0;
}

static const struct file_operations green_tee_fops = {
    .unlocked_ioctl = green_tee_ioctl,
};

static struct miscdevice green_tee_dev = {
    .name = "green_tee",
    .fops = &green_tee_fops
};

static int green_tee_dev_init(void){
    int ret;

    ret = misc_register(&green_tee_dev);
    if(ret){
        printk("Green TEE Device Initialization Failed.\n");
        return -EFAULT;
    }

    return 0;

}

int green_tee_init(void){

    int ret = 0;;

    ret = green_tee_arch_init();
    if(ret < 0) goto green_tee_init_fail;

    ret = green_tee_dev_init();
    if(ret < 0) goto green_tee_init_fail;
    
    return ret;

green_tee_init_fail:
    return -EFAULT;
}

device_initcall(green_tee_init);
