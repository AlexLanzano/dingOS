include $(DINGOS_CONF)

OBJ = $(wildcard *.o)

all:
	$(CC) $(CFLAGS) x86_64_boot.o -Ttext 0x7c00 -o bootloader.elf
	$(CC) $(CFLAGS) $(LINK) x86_64_kernel_entry.o x86_64_main.o -o kernel.elf
	$(OBJCOPY) $(DINGOS_PATH)/build/bootloader.elf -O binary $(DINGOS_PATH)/build/bootloader.bin
	$(OBJCOPY) $(DINGOS_PATH)/build/kernel.elf -O binary $(DINGOS_PATH)/build/kernel.bin
	@cat $(DINGOS_PATH)/build/bootloader.bin $(DINGOS_PATH)/build/kernel.bin > $(DINGOS_PATH)/dingos.img
clean:
	@$(RM) $(OBJ)
	@$(RM) *.elf
