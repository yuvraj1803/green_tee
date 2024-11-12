DEBUG ?= 1
NPROC ?= $(shell nproc)
ROOT  ?= $(shell pwd)

all: buildroot u-boot linux tfa tee client

clean: clean_tfa clean_linux clean_u-boot clean_tee clean_buildroot

# Green TEE
.PHONY: tee
tee:
	cd tee/ && make

clean_tee:
	cd tee/ && make clean

# U-Boot
.PHONY: u-boot
u-boot:
	cd u-boot && make qemu_arm64_defconfig && make -j$(NPROC)

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
	     QEMU_USE_GIC_DRIVER=QEMU_GICV3 \
	     BL32_RAM_LOCATION=tdram \
	     BL32=$(ROOT)/tee/build/tee.bin \
	     -j$(NPROC) \
	     SPD=green_teed

ifeq ($(DEBUG),1)
TFA_BUILD_PATH=arm-trusted-firmware/build/qemu/debug/
else
TFA_BUILD_PATH=arm-trusted-firmware/build/qemu/release/
endif

tfa: linux u-boot tee
	cd arm-trusted-firmware && make $(TFA_FLAGS) all fip
	cp $(TFA_BUILD_PATH)/qemu_fw.bios $(TFA_BUILD_PATH)/../
clean_tfa:
	rm -f $(TFA_BUILD_PATH)/../qemu_fw.bios
	cd arm-trusted-firmware && make clean

# Buildroot
.PHONY: buildroot
buildroot:
	cd buildroot/ && make qemu_aarch64_virt_defconfig && make -j$(NPROC)
clean_buildroot:
	cd buildroot/ && make clean

# Linux Kernel

LINUX_FLAGS ?= \
               ARCH=arm64 \
               CROSS_COMPILE=aarch64-linux-gnu- \
	       -j$(NPROC)

.PHONY: linux
linux: buildroot
	cd linux && make defconfig && make $(LINUX_FLAGS) Image
	cp buildroot/output/images/rootfs.ext4 linux/
clean_linux:
	cd linux && make clean
	rm -f linux/rootfs.ext4

# Client
.PHONY: client
client: linux
	cd client && make
	sudo sh mount_client.sh
clean_client:
	cd client && make clean
	sudo sh clean_client.sh
# Run
QEMU_ARGS ?= \
	     -nographic \
	     -kernel linux/arch/arm64/boot/Image \
	     -cpu max \
	     -smp 1 \
	     -machine virt,secure=on,gic-version=3 \
	     -bios $(TFA_BUILD_PATH)/../qemu_fw.bios \
	     -drive file=linux/rootfs.ext4,if=none,format=raw,id=hd0 -device virtio-blk-device,drive=hd0 \
	     -m 2G \
	     -append "rootwait nokaslr root=/dev/vda init=/sbin/init console=ttyAMA0" \
	     -serial mon:stdio \
	     -serial tcp:localhost:12345

run:
	qemu-system-aarch64 $(QEMU_ARGS)

debug:
	qemu-system-aarch64 $(QEMU_ARGS) -s -S

GDB_ARGS ?= \
	    -ex "set confirm off" \
	    -ex "add-symbol-file arm-trusted-firmware/build/qemu/debug/bl1/bl1.elf" \
	    -ex "add-symbol-file arm-trusted-firmware/build/qemu/debug/bl2/bl2.elf" \
	    -ex "add-symbol-file arm-trusted-firmware/build/qemu/debug/bl31/bl31.elf" \
	    -ex "add-symbol-file linux/vmlinux" \
	    -ex "add-symbol-file tee/build/tee.elf" \
	    -ex "target remote localhost:1234"

gdb:
	gdb-multiarch $(GDB_ARGS)

nc:
	nc -l 12345 -k
