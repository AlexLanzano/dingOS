include $(DINGOS_MAKEFILE_INCLUDE)

OBJ = $(wildcard *.o)


rpi2:
	$(CC) $(LINK) $(CFLAGS) $(OBJ) -o kernel.elf
	$(OBJCOPY) $(DINGOS_PATH)/build/kernel.elf -O binary kernel7.img

x86:
	$(CC) $(LINK) $(CFLAGS) $(OBJ) -o kernel.elf
	$(OBJCOPY) $(DINGOS_PATH)/build/kernel.elf -O binary dingos.img


