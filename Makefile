GCC = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy

CFLAGS = -O2 -mfpu=neon-vfpv4 -mfloat-abi=hard -march=armv7-a -mtune=cortex-a7 -ffreestanding -nostdlib -nostartfiles -Iinclude/
CVERSION = -std=gnu99
LINK = -T init/linker.ld

INIT = init/boot.S init/start.c init/main.c 
BUILD = build/
DRIVERS = drivers/gpio.c drivers/timer.c
MEMORY = memory/alloc.c memory/filesystem.c
LIB = lib/string.c
INTERRUPT = interrupt/vector_table.S interrupt/arm_timer.c interrupt/interrupt_handlers.c

SOURCE = $(INIT) $(DRIVERS) $(MEMORY) $(LIB) $(INTERRUPT)

all: main


main:
	$(GCC) $(CFLAGS) $(CVERSION) $(LINK) $(SOURCE) -o $(BUILD)kernel.elf
	$(OBJCOPY) $(BUILD)kernel.elf -O binary kernel7.img
