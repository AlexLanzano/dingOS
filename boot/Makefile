SRC := boot.S
SRC += startc.c

OBJ := boot.o
OBJ += startc.o

.PHONY: all
all: build link

.PHONY: clean
clean:
	rm $(OBJ) *.elf

.PHONY: build
build: $(OBJ)

%.o: %.c
	$(CC) -c $(CFLAGS) -m32 $(INCLUDE_PATH) -o $@ $^

%.o: %.S
	$(CC) -c $(CFLAGS) -m32 $(INCLUDE_PATH) -o $@ $^

.PHONY: link
link:
	$(LD) --omagic -o test.elf -static -m elf_i386 -Ttext 0x7c00 $(OBJ)
	$(OBJCOPY) test.elf -O binary test.img
