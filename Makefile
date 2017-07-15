include $(DINGOS_PATH)/Makefile.inc

SUBDIRS = init libc memory drivers build

all: $(SUBDIRS) objcopy

$(SUBDIRS):
	$(MAKE) -C $@

objcopy:
	$(OBJCOPY) $(DINGOS_PATH)/build/kernel.elf -O binary kernel7.img

.PHONY: all $(SUBDIRS)

clean:
	rm build/*.o
