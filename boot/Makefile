SRC := boot.S
SRC += startc.c

OBJ := boot.o
OBJ += startc.o

.PHONY: all
all: build

.PHONY: clean
clean:
	rm $(OBJ) *.elf

.PHONY: build
build: $(OBJ)

%.o: %.c
	$(CC) -c $(CFLAGS) -m32 $(INCLUDE_PATH) -o $@ $^

%.o: %.S
	$(CC) -c $(CFLAGS) -m32 $(INCLUDE_PATH) -o $@ $^
