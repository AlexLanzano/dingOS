include $(DINGOS_CONF)

SRC := $(wildcard *.c)
SRC += $(wildcard *.S)
OBJ := $(SRC:.c=.o)
OBJ += $(SRC:.S=.o)

all: $(OBJ)

%.o: %.c
	$(CC) -c  $(CFLAGS) $(INCLUDE_PATH) -o $(TARGET_DIR)$@ $^
%.o: %.S
	$(CC) -c  $(CFLAGS) $(INCLUDE_PATH) -o $(TARGET_DIR)$@ $^
