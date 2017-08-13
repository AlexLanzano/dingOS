include $(DINGOS_MAKEFILE_INCLUDE)


SUBDIRS = init libc memory drivers build


all:
	@echo "Please specify the architecture: x86 or rpi2"

rpi2: export DINGOS_PATH = $(shell pwd)
rpi2: export RULE = rpi2
rpi2: export DINGOS_MAKEFILE_INCLUDE = $(DINGOS_PATH)/Makefile_rpi2.inc
rpi2: $(SUBDIRS)

x86: export DINGOS_PATH = $(shell pwd)
x86: export RULE = x86
x86: export DINGOS_MAKEFILE_INCLUDE = $(DINGOS_PATH)/Makefile_x86.inc
x86: $(SUBDIRS)

$(SUBDIRS):
	$(MAKE) $(RULE) -C $@



.PHONY: x86 $(SUBDIRS)


clean:
	rm build/*.o
	rm build/*.elf
