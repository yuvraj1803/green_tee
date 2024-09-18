#include <stdio.h>
#include <green_tee.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <sys/ioctl.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/stat.h>
#include <ctype.h>

int min(int x, int y){
	if(x > y) return y;

	return x;
}

int main(int argc, char* argv[]){

	if(argc < 2) return 1;

	int tee_fd = open("/dev/green_tee", O_RDWR);
	if(tee_fd < 0){
		printf("client: error opening /dev/green_tee\n");
		exit(1);
	}


	int fd = open(argv[1], O_RDWR);
	if(fd < 0){
		printf("client: could not open the file\n");
		exit(1);
	}

	struct stat st;
	stat(argv[1], &st);

	// when kernel copies back encrypted/decrypted data using copy_to_user(), it expects buffer to be aligned to 16 bytes.


	char buff[4096] __attribute__((aligned (16)));
	if(!buff){
		printf("client: failed to allocate buffer\n");
		exit(1);
	}

	for(int i=0; i < st.st_size;i+=4096){
		
		memset(buff, 0, sizeof(buff));

		// reading from file to buffer

		if(lseek(fd, min(st.st_size, i), SEEK_SET) < 0){
			printf("client: failed to seek file\n");
			exit(1);
		}

		if(!read(fd, buff, min(4096, st.st_size < 4096 ? st.st_size : st.st_size))){
			printf("client: failed to read file\n");
			exit(1);
		}

		// encrypting buffer using TEE

		if(ioctl(tee_fd, GREEN_TEE_ENCRYPT, buff) < 0){
			printf("client: GREEN_TEE_ENCRYPT ioctl() failed\n");
			exit(1);
		}

		// writing back to file from buffer

		if(lseek(fd, min(st.st_size, i), SEEK_SET) < 0){
			printf("client: failed to seek file\n");
			exit(1);
		}

		if(!write(fd, buff, min(4096, st.st_size < 4096 ? st.st_size : st.st_size))){
			printf("client: failed to write back to file\n");
			exit(1);
		}

	}


	return 0;
}
