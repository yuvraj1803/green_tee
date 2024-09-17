#ifndef __OTP_H__
#define __OTP_H__

#include <stdint.h>

void otp_init();
uint64_t otp_get_key();
void otp_enc_buffer(uint64_t* buff, uint64_t size);
void otp_dec_buffer(uint64_t* buff, uint64_t size);

#endif