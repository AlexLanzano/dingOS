include $(DINGOS_CONF)

OBJ = $(wildcard *.o)

all:
	$(CC) $(CFLAGS) boot.o -Ttext 0x7c00 -o kernel.elf
	$(OBJCOPY) $(DINGOS_PATH)/build/kernel.elf -O binary $(DINGOS_PATH)/dingos.img

clean:
	@$(RM) $(OBJ)
	@$(RM) *.elf
