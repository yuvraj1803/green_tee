INC=./include
TOOLCHAIN=@aarch64-linux-gnu-
CC=$(TOOLCHAIN)gcc
AS=$(TOOLCHAIN)as
LD=$(TOOLCHAIN)ld
OBJCOPY=$(TOOLCHAIN)objcopy
OBJDUMP=$(TOOLCHAIN)objdump

CFLAGS=-g -ffreestanding -nostdlib -nostartfiles -Wall -I$(INC)
ASMFLAGS=-g -I$(INC)

OBJ += ./build/boot/boot.S.o

all: tee.elf

./build/boot/%.S.o: ./boot/%.S
	mkdir -p build/boot/
	@echo CC $@
	$(CC) $(ASMFLAGS) -c $< -o $@

tee.elf: $(OBJ)
	$(LD) -T linker.ld.S -o build/tee.elf $(OBJ)
	$(OBJCOPY) build/tee.elf -O binary build/tee.bin

objdump: tee.elf
	$(OBJDUMP) -D build/tee.elf > build/tee.dump

clean:
	rm -rf build/

