include $(DINGOS_CONF)

OBJ = $(wildcard *.o)

all:
	$(CC) $(LINK) $(CFLAGS) $(OBJ) -o kernel.elf
	$(OBJCOPY) $(DINGOS_PATH)/build/kernel.elf -O binary $(DINGOS_PATH)/dingos.img

clean:
	@$(RM) $(OBJ)
	@$(RM) *.elf
