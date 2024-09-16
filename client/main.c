#include <stdio.h>
#include <green_tee.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <sys/ioctl.h>


int main(){

	int tee_fd = open("/dev/green_tee", O_RDWR);
	if(tee_fd < 0){
		printf("client: error opening /dev/green_tee\n");
		exit(1);
	}

	struct green_tee_print_data print_data;
	print_data.str = "this is from linux";
	print_data.len = strlen(print_data.str);

	if(ioctl(tee_fd, GREEN_TEE_PRINT, &print_data) < 0){
		printf("client: print data ioctl failed!");
	}

	return 0;
}