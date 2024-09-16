#ifndef __GREEN_TEE_H__
#define __GREEN_TEE_H__

/* Although linux kernel drivers use _IO, _IOW, etc. for ioctl numbering, but since this project is not that serious,
	I will just use some simple numbers to identify these ioctls */

enum green_tee_ioctls{
	GREEN_TEE_PRINT
};

struct green_tee_print_data{
	char* str; // userspace address
	int len;
};


#endif