#pragma GCC push_options
#pragma GCC optimize ("O0")

#include <linux/green_tee/green_tee.h>
#include <linux/printk.h>
#include <linux/kernel.h>
#include <linux/errno.h>
#include <linux/fs.h>
#include <linux/miscdevice.h>
#include <linux/slab.h>

#include <asm/io.h>

static int green_tee_dev_initialised = 0;

static long green_tee_ioctl(struct file* file, unsigned int ioctl, unsigned long arg){

    if(!green_tee_dev_initialised) return -EINVAL;

    switch(ioctl){
    case GREEN_TEE_PRINT:
        struct green_tee_print_data print_data;

        if(copy_from_user(&print_data, (void*) arg, sizeof(struct green_tee_print_data))){
            return -EPERM;
        }

        char* __str = kzalloc(print_data.len, GFP_KERNEL);
        if(!__str) return -ENOMEM;

        strncpy_from_user(__str, print_data.str, print_data.len);

        print_data.str = __str;

        if(green_tee_arch_print_data(&print_data)){
            kfree(__str);
            return -EPERM;
        }

        break;  
    case GREEN_TEE_ENCRYPT:

        char* buff = (char*) kzalloc(4096, GFP_KERNEL);
        if(!buff){
            return -ENOMEM;
        }

        strncpy_from_user(buff, (char*) arg, 4096);

        if(green_tee_arch_encrypt_data(buff)){
            return -EPERM;
        }

        if(copy_to_user((void*)arg, (void*)buff, 4096)){
            kfree(buff);
            return -EPERM;
        }

        kfree(buff);

        break;
    case GREEN_TEE_DECRYPT:

        buff = (char*) kzalloc(4096, GFP_KERNEL);
        if(!buff){
            return -ENOMEM;
        }

        strncpy_from_user(buff, (char*) arg, 4096);

        if(green_tee_arch_decrypt_data(buff)){
            return -EPERM;
        }

        if(copy_to_user((void*)arg, (void*)buff, 4096)){
            kfree(buff);
            return -EPERM;
        }

        kfree(buff);

        break;

    default:
        return -EINVAL;
    }

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
        return -EINVAL;
    }

    return 0;

}

int green_tee_init(void){

    int ret = 0;;

    ret = green_tee_arch_init();
    if(ret < 0) goto green_tee_init_fail;

    ret = green_tee_dev_init();
    if(ret < 0) goto green_tee_init_fail;

    green_tee_dev_initialised = 1;
    
    return ret;

green_tee_init_fail:
    return -EFAULT;
}

device_initcall(green_tee_init);


#pragma GCC pop_options