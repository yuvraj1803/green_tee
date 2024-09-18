#ifndef __GREEN_TEE__
#define __GREEN_TEE__

#include <linux/ioctl.h>

struct green_tee_print_data{
	char* str; // userspace address
	int len;
};

#define	GREEN_TEE_PRINT 	_IOR('y', 0, struct green_tee_print_data)
#define GREEN_TEE_ENCRYPT 	_IOW('y',1, char*)
#define GREEN_TEE_DECRYPT   _IOW('y',2, char*)



int green_tee_arch_print_data(struct green_tee_print_data* print_data);
int green_tee_arch_encrypt_data(char* buff);
int green_tee_arch_decrypt_data(char* buff);
int green_tee_arch_init(void);
int green_tee_init(void);

#endif
