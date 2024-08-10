DEBUG ?= 1
NPROC ?= $(shell nproc)
ROOT  ?= $(shell pwd)

all: u-boot linux tfa

clean: clean_tfa clean_linux clean_u-boot

# U-Boot
.PHONY: u-boot
u-boot:
	cp configs/u-boot_config u-boot/.config
	cd u-boot && make -j$(NPROC)

clean_u-boot:
	cd u-boot && make clean

# ARM Trusted Firmware

TFA_FLAGS ?= \
	     CROSS_COMPILE=aarch64-linux-gnu- \
	     PLAT=qemu \
	     BL33=$(ROOT)/u-boot/u-boot.bin \
	     DEBUG=$(DEBUG) \
	     LOG_LEVEL=40 \
	     ARM_LINUX_KERNEL_AS_BL33=0 \
	     -j$(NPROC)

tfa: linux
	cd arm-trusted-firmware && make $(TFA_FLAGS) all fip
clean_tfa:
	cd arm-trusted-firmware && make clean && make realclean

# Linux Kernel

LINUX_FLAGS ?= \
               ARCH=arm64 \
               CROSS_COMPILE=aarch64-linux-gnu- \
	       -j$(NPROC)

.PHONY: linux
linux:
	cp configs/linux_config linux/.config
	cd linux && make $(LINUX_FLAGS)

clean_linux:
	cd linux && make clean

# Run
QEMU_ARGS ?= \
	     -nographic \
	     -kernel linux/arch/arm64/boot/Image \
	     -cpu cortex-a72 \
	     -smp 1 \
	     -machine virt,secure=on \
	     -bios arm-trusted-firmware/build/qemu/debug/qemu_fw.bios \
	     -drive file=linux/rootfs.ext4,if=none,format=raw,id=hd0 -device virtio-blk-device,drive=hd0 \
	     -m 2G \
	     -append "rootwait nokaslr root=/dev/vda init=/sbin/init console=ttyAMA0"

run:
	qemu-system-aarch64 $(QEMU_ARGS)
