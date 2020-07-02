export DINGOS_ARCH = x86_64
export DINGOS_PATH := $(shell pwd)
KERNEL_PATH := $(DINGOS_PATH)/kernel/$(DINGOS_ARCH)

CC := $(DINGOS_PATH)/compiler/bin/$(DINGOS_ARCH)-elf-gcc
OBJCOPY := $(DINGOS_PATH)/compiler/bin/$(DINGOS_ARCH)-elf-objcopy
LD := $(DINGOS_PATH)/compiler/bin/$(DINGOS_ARCH)-elf-ld

CFLAGS = -Werror -Wall -Wextra -ffreestanding -nostdlib -g
LDFLAGS = --omagic -static
INCLUDE_PATH = -I ./common

BOOT_END = 0x$(shell nm $(BOOT_ELF) | grep " _end" | cut -f 1 -d " ")

SUBDIRS = \
bootloader \
kernel \

SRC = \
bootloader/boot.S \
bootloader/startc.c \
bootloader/memory.c \
bootloader/asm.c \
kernel/main.c \
kernel/vga.c \

BOOT_OBJ = \
bootloader/boot.o \
bootloader/asm.o \
bootloader/startc.o \
bootloader/memory.o \

OBJ = \
kernel/main.o \
kernel/vga.o

BOOT_ELF = bootloader.elf
KERNEL_ELF = kernel.elf

all: dingOS-x86_64.img

.PHONY: compiler
compiler:
	mkdir -p compiler
	scripts/build-compiler.sh $(DINGOS_ARCH)

clean-compiler:
	rm -rf compiler/*

$(BOOT_OBJ): CFLAGS += -m32

%.o: %.c
	$(CC) -c $(CFLAGS) $(INCLUDE_PATH) -o $@ $^

%.o: %.S
	$(CC) -c $(CFLAGS) $(INCLUDE_PATH) -o $@ $^

$(BOOT_ELF): $(BOOT_OBJ)
	$(LD) $(LDFLAGS) -m elf_i386 -Ttext 0x7c00 -o $@ $^

$(KERNEL_ELF): $(OBJ)
	$(LD) $(LDFLAGS) -m elf_x86_64 -e main -Ttext $(BOOT_END) -o $@ $^

dingOS-x86_64.img: $(BOOT_ELF) $(KERNEL_ELF)
	$(OBJCOPY) $(BOOT_ELF) --set-section-flag .bss=alloc,load,contents -O binary boot.img
	$(OBJCOPY) $(KERNEL_ELF) -O binary kernel.img
	cat boot.img kernel.img > $(DINGOS_PATH)/dingos-x86_64.img
	chmod 777 $(DINGOS_PATH)/dingos-x86_64.img

.PHONY: clean
clean:
	rm -f $(BOOT_OBJ) $(OBJ) boot.elf kernel.elf *.img


# Debug Targets
run:
	qemu-system-x86_64 -hda dingos-x86_64.img -d in_asm

run-debug:
	qemu-system-x86_64 -s -S -hda dingos-x86_64.img -d in_asm,guest_errors,cpu_reset

run-debug-boot:
	qemu-system-i386 -s -S -hda dingos-x86_64.img -d in_asm,guest_errors -nographic

gdb:
	gdb -ex "file kernel/x86_64/kernel.elf" -ex "set arch i386:x86-64" -ex "target remote localhost:1234"

gdb-boot:
	gdb -ex "file kernel/x86_64/boot.elf" -ex "set arch i386" -ex "target remote localhost:1234"
