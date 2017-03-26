GCC = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy

CFLAGS = -O2 -mfpu=neon-vfpv4 -mfloat-abi=hard -march=armv7-a -mtune=cortex-a7 -ffreestanding -nostartfiles -Iinclude/
CVERSION = -std=gnu99
LINK = -T init/linker.ld

INIT = init/boot.S init/start.c init/main.c 
BUILD = build/
DRIVERS = drivers/gpio.c drivers/timer.c mini_uart/aux.c
MEMORY = memory/alloc.c memory/filesystem.c memory/mem.c
LIB = lib/string.c
INTERRUPT = interrupt/vector_table.S interrupt/arm_timer.c interrupt/interrupt_handlers.c
GRAPHICS = graphics/mailbox.s graphics/frame_buffer.s graphics/draw.c graphics/font.S

SOURCE = $(INIT) $(DRIVERS) $(MEMORY) $(LIB) $(INTERRUPT) $(GRAPHICS)

all: main


main:
	$(GCC) $(CFLAGS) $(CVERSION) $(LINK) $(SOURCE) -o $(BUILD)kernel.elf
	$(OBJCOPY) $(BUILD)kernel.elf -O binary kernel7.img
