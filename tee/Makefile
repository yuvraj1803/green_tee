INC=./include
TOOLCHAIN=@aarch64-linux-gnu-
CC=$(TOOLCHAIN)gcc
AS=$(TOOLCHAIN)as
LD=$(TOOLCHAIN)ld
OBJCOPY=$(TOOLCHAIN)objcopy
OBJDUMP=$(TOOLCHAIN)objdump

CFLAGS=-g -mgeneral-regs-only -ffreestanding -nostdlib -nostartfiles -Wall -I$(INC)
ASMFLAGS=-g -I$(INC)

OBJ += ./build/boot/boot.S.o
OBJ += ./build/kernel/main.o
OBJ += ./build/kernel/panic.o
OBJ += ./build/drivers/pl011.o
OBJ += ./build/mm/io.S.o
OBJ += ./build/mm/mm.o
OBJ += ./build/lib/stdio.o
OBJ += ./build/lib/string.o
OBJ += ./build/lib/stdlib.o

all: build_setup tee.elf

build_setup:
	chmod +x ./install.sh
	./install.sh

./build/boot/%.S.o: ./boot/%.S
	@echo CC $<
	$(CC) $(ASMFLAGS) -c $< -o $@

./build/kernel/%.o: ./kernel/%.c
	@echo CC $<
	$(CC) $(CFLAGS) -c $< -o $@

./build/mm/%.o: ./mm/%.c
	@echo CC $<
	$(CC) $(CFLAGS) -c $< -o $@

./build/mm/%.S.o: ./mm/%.S
	@echo CC $<
	$(CC) $(ASMFLAGS) -c $< -o $@

./build/drivers/%.o: ./drivers/%.c
	@echo CC $<
	$(CC) $(CFLAGS) -c $< -o $@

./build/lib/%.o: ./lib/%.c
	@echo CC $<
	$(CC) $(CFLAGS) -c $< -o $@

tee.elf: $(OBJ)
	$(LD) -T linker.ld.S -o build/tee.elf $(OBJ)
	$(OBJCOPY) build/tee.elf -O binary build/tee.bin

objdump: tee.elf
	$(OBJDUMP) -D build/tee.elf > build/tee.dump

clean:
	rm -rf build/

