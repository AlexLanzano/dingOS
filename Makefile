GCC = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy

CFLAGS = -O2 -mfpu=neon-vfpv4 -mfloat-abi=hard -march=armv7-a -mtune=cortex-a7 -nostartfiles -Iinclude/
CVERSION = -std=gnu99
LINK = -T init/linker.ld

INIT = init/boot.S init/start.c init/main.c 
BUILD = build/
DRIVERS = drivers/gpio.c drivers/timer.c
MEMORY = memory/mmu.S

all: main


main:
	$(GCC) $(CFLAGS) $(CVERSION) $(LINK) $(DRIVERS) $(INIT) $(MEMORY) -o $(BUILD)kernel.elf
	$(OBJCOPY) $(BUILD)kernel.elf -O binary kernel7.img
