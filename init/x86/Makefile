include $(DINGOS_MAKEFILE_INCLUDE)
C = $(wildcard *.c)
COBJ = $(SRC:.c=.o)
ASM = $(wildcard *.S)
AOBJ = $(ASM:.S=.o)

SRC = $(C) $(ASM)
OBJ = $(COBJ) $(AOBJ)

all: $(OBJ)

%.o: %.c
	$(CC) -c  $(CFLAGS) $(INCLUDE_PATH) -o $(TARGET_DIR)$@ $^

%.o: %.S
	$(CC) -c  $(CFLAGS) $(INCLUDE_PATH) -o $(TARGET_DIR)$@ $^



