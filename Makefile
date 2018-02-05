MAKEFLAGS += --no-print-directory
SUBDIRS := $(wildcard */.)
EXCLUDE := compiler/. img/. build/. resources/. include/. user_space/. scripts/.
SUBDIRS := $(filter-out $(EXCLUDE), $(SUBDIRS))

all: export DINGOS_PATH = $(shell pwd)
all: export DINGOS_CONF = $(DINGOS_PATH)/Makefile.conf
all: $(SUBDIRS)
all: build

install:
	@scripts/install_binutils.sh
	@scripts/install_gcc.sh

$(SUBDIRS):
	@$(MAKE) -C $@

build:
	@$(MAKE) -C build/.

run:
	@qemu-system-x86_64 -drive file=dingos.img,if=floppy,format=raw -d in_asm,guest_errors

clean:
	@rm -f build/*.o
	@rm -f build/*.elf
	@rm -f dingos.img

clean_compiler:
	@rm -rf compiler/*

.PHONY: $(SUBDIRS) build
