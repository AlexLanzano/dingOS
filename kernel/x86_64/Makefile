CC := $(DINGOS_PATH)/compiler/bin/$(DINGOS_ARCH)-elf-gcc
OBJCOPY := $(DINGOS_PATH)/compiler/bin/$(DINGOS_ARCH)-elf-objcopy
LD := $(DINGOS_PATH)/compiler/bin/$(DINGOS_ARCH)-elf-ld

CFLAGS = -Werror -Wall -Wextra -ffreestanding -nostdlib -g
LDFLAGS = --omagic -static
INCLUDE_PATH = -I ./include

BOOT_END = 0x$(shell nm boot.elf | grep " _end" | cut -f 1 -d " ")

SUBDIRS = \
boot \
main \

SRC = \
boot/boot.S \
boot/startc.c \
boot/memory.c \
boot/asm.c \
main/main.c

BOOT_OBJ = \
boot/boot.o \
boot/asm.o \
boot/startc.o \
boot/memory.o \

OBJ = \
main/main.o

BOOT_ELF = boot.elf
KERNEL_ELF = kernel.elf

all: dingOS-x86_64.img

$(BOOT_OBJ): CFLAGS += -m32

%.o: %.c
	$(CC) -c $(CFLAGS) $(INCLUDE_PATH) -o $@ $^

%.o: %.S
	$(CC) -c $(CFLAGS) $(INCLUDE_PATH) -o $@ $^

boot.elf: $(BOOT_OBJ)
	$(LD) $(LDFLAGS) -m elf_i386 -Ttext 0x7c00 -o $@ $^

kernel.elf: $(OBJ)
	$(LD) $(LDFLAGS) -m elf_x86_64 -e main -Ttext $(BOOT_END) -o $@ $^

dingOS-x86_64.img: boot.elf kernel.elf
	$(OBJCOPY) boot.elf --set-section-flag .bss=alloc,load,contents -O binary boot.img
	$(OBJCOPY) kernel.elf -O binary kernel.img
	cat boot.img kernel.img > $(DINGOS_PATH)/dingos-x86_64.img
	chmod 777 $(DINGOS_PATH)/dingos-x86_64.img

clean:
	rm -f $(BOOT_OBJ) $(OBJ) boot.elf kernel.elf
