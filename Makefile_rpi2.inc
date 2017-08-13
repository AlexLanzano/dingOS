CC = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy
TARGET_DIR = $(DINGOS_PATH)/build/
INCLUDE_PATH = -I$(DINGOS_PATH)/include -I$(DINGOS_PATH)/include/drivers/cpu/ -I$(DINGOS_PATH)/include/drivers/gpu \
		       -I$(DINGOS_PATH)/include/memory -I$(DINGOS_PATH)/include/libc -I$(DINGOS_PATH)/include/filesystem

CFLAGS =  -mfpu=neon-vfpv4 -mfloat-abi=hard -march=armv7-a -mtune=cortex-a7 -ffreestanding -nostartfiles
LINK = -T $(DINGOS_PATH)/init/rpi2/linker.ld

