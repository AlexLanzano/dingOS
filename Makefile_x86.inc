CC = /opt/cross/bin/i686-elf-gcc
OBJCOPY = /opt/cross/bin/i686-elf-objcopy
CFLAGS = -std=gnu99 -ffreestanding -Wall -Wextra -nostdlib -nostartfiles
TARGET_DIR = $(DINGOS_PATH)/build/
INCLUDE_PATH = -I$(DINGOS_PATH)/include -I$(DINGOS_PATH)/include/drivers/cpu/ -I$(DINGOS_PATH)/include/drivers/gpu \
		       -I$(DINGOS_PATH)/include/memory -I$(DINGOS_PATH)/include/libc -I$(DINGOS_PATH)/include/filesystem

LINK = -T $(DINGOS_PATH)/init/x86/linker.ld