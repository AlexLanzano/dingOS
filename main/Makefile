SRC := dingos.c

OBJ := dingos.o

.PHONY: all
all: build

.PHONY: clean
clean:
	rm $(OBJ) *.elf

.PHONY: build
build: $(OBJ)

%.o: %.c
	$(CC) -c $(CFLAGS) $(INCLUDE_PATH) -o $@ $^

%.o: %.S
	$(CC) -c $(CFLAGS) $(INCLUDE_PATH) -o $@ $^
