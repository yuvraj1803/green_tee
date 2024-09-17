#include <crypto/otp.h>
#include <stdint.h>
#include <lib/stdio.h>

static uint64_t otp_key = 0;

void otp_init(){
	do{
		otp_key = otp_get_key();
		otp_key <<= 32;
		otp_key |= otp_get_key();
	}while(otp_key == 0);


	LOG("One Time Pad Initialised\n");
}

void otp_enc_buffer(uint64_t* buff, uint64_t size){
	for(int i = 0; i < size; i++){
		buff[i] ^= otp_key;
	}
}

void otp_dec_buffer(uint64_t* buff, uint64_t size){
	for(int i = 0; i < size; i++){
		buff[i] ^= otp_key;
	}
}