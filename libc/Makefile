include $(DINGOS_PATH)/Makefile.inc

C = $(wildcard *.c)
COBJ = $(SRC:.c=.o)
ASM = $(wildcard *.S)
AOBJ = $(ASM:.S=.o)

SRC = $(C) $(ASM)
OBJ = $(COBJ) $(AOBJ)

all: $(OBJ)

%.o: %.c
	$(CC) -c  $(CFLAGS) $(INCLUDE_PATH) -o $(TARGET_DIR)$@ $^
