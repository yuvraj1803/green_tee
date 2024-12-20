# Green TEE: A Trusted Execution Environment (ARM TrustZone)
Green TEE is a Trusted OS designed to run in Secure-EL1 (S-EL1) mode on processors supporting ARM Trustzone.
This project has 8 components which put together gives a working Linux Kernel in NS-EL1 and Green TEE running in S-EL1.
- **Arm Trusted Firmware**: arm-trusted-firmware/
- **Green TEE Secure Payload Dispatcher (inside TF-A as EL3 runtime service)**: arm-trusted-firmware/services/spd/green_teed/
- **Buildroot**: buildroot/
- **U-Boot**: u-boot/
- **Linux Kernel**: linux/
- **Linux Kernel TEE Driver**: linux/drivers/green_tee
- **Green TEE Core**: /tee
- **Linux Userspace Client**: /client
  
![Screenshot from 2024-09-18 13-58-45](https://github.com/user-attachments/assets/64f09804-2c8e-4f38-9950-860cd0d1f772)


The build system is designed to highly simplify the compilation process as these components have various build-time configurations.

The userspace client can use ioctl() to issue requests to the Linux Kernel which passes relevant information to TF-A through an SMC call. TF-A then switches context to Green TEE where the request is processed.

## Services currently supported by TEE
- **GREEN_TEE_PRINT**: Print a string in the Secure World terminal sent by NS-EL0 application.
- **GREEN_TEE_ENCRYPT**: Encrypt a buffer passed from NS-EL0 using the One Time Pad cryptographic algorithm.
- **GREEN_TEE_DECRYPT**: Decrypt a buffer passed from NS-EL0 using the One Time Pad cryptographic algorithm.

## Building
`chmod +x ./install.sh`

`./install.sh`

`make`

## Running
QEMU forwards S-EL1's serial device data to localhost:12345. A netcat connection has to be established on another terminal.

`make nc` (terminal 2)

`make run`(terminal 1)

## Example
**Upper Terminal**: Green TEE

**Lower Terminal**: Linux Kernel


![Screenshot from 2024-11-29 12-53-26](https://github.com/user-attachments/assets/ab369bd7-dda1-41de-9bc8-82436bf97634)

	
