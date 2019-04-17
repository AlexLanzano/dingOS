DINGOS_PATH := $(shell pwd)
DINGOS_ARCH = x86_64-elf64

CC := $(DINGOS_PATH)/compiler/cross/bin/gcc
OBJCOPY := $(DINGOS_PATH)/compiler/cross/bin/objcopy
LD := $(DINGOS_PATH)/compiler/cross/bin/ld
GDB := $(DINGOS_PATH)/compiler/cross/bin/$(DINGOS_ARCH)-gdb

CFLAGS = -Werror -Wall -Wextra -ffreestanding -nostdlib -g

INCLUDE_PATH = -I $(DINGOS_PATH)/include -I $(DINGOS_PATH)/include/arch

BOOT_END = 0x$(shell nm boot.elf | grep " _end" | cut -f 1 -d " ")

SUBDIRS = \
boot \
main \

SRC = \
boot/boot.S \
boot/startc.c \
boot/memory.c \
boot/asm.c \
main/dingos.c

BOOT_OBJ =\
boot/boot.o \
boot/asm.o \
boot/startc.o \
boot/memory.o \

OBJ = \
main/dingos.o

.PHONY: all
all: build boot_link link build_image

.PHONY: build
build: $(BOOT_OBJ) $(OBJ)

$(BOOT_OBJ): CFLAGS += -m32

%.o: %.c
	$(CC) -c $(CFLAGS) $(INCLUDE_PATH) -o $@ $^

%.o: %.S
	$(CC) -c $(CFLAGS) $(INCLUDE_PATH) -o $@ $^

.PHONY: boot_link
boot_link:
	$(LD) --omagic -o boot.elf -static -m elf_i386 -Ttext 0x7c00 $(BOOT_OBJ)
	$(OBJCOPY) boot.elf -O binary boot.img

.PHONY: link
link:
	$(LD) --omagic -o kernel.elf -static -m elf_x86_64 -e main -Ttext $(BOOT_END) $(OBJ)
	$(OBJCOPY) kernel.elf -O binary kernel.img

.PHONY: build_image
build_image:
	cat boot.img kernel.img > dingos.img

.PHONY: clean
clean:
	rm $(BOOT_OBJ) $(OBJ) boot.elf kernel.elf dingos.img

.PHONY: compiler
compiler:
	mkdir -p compiler
	scripts/build-compiler.sh

.PHONY: clean-compiler
clean-compiler:
	rm -rf compiler/*

.PHONY: run
run:
	qemu-system-x86_64 -hda dingos.img -d cpu_reset -nographic

.PHONY: run-debug
run-debug:
	qemu-system-x86_64 -s -S -hda dingos.img -d in_asm,guest_errors,cpu_reset -nographic

.PHONY: run-debug-boot
run-debug-boot:
	qemu-system-i386 -s -S -hda dingos.img -d in_asm,guest_errors -nographic

.PHONY: gdb
gdb:
	gdb -ex "file boot.elf" -ex "set arch i386:x86-64" -ex "target remote localhost:1234"

.PHONY: gdb
gdb-boot:
	gdb -ex "file boot.elf" -ex "set arch i386" -ex "target remote localhost:1234"
