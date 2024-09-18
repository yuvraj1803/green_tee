#ifndef __GREEN_TEE_H__
#define __GREEN_TEE_H__

#include <linux/ioctl.h>

struct green_tee_print_data{
	char* str; // userspace address
	int len;
};

#define	GREEN_TEE_PRINT 	_IOR('y', 0, struct green_tee_print_data)
#define GREEN_TEE_ENCRYPT 	_IOW('y',1, char*)
#define GREEN_TEE_DECRYPT   _IOW('y',2, char*)




#endif