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


.PHONY: $(SUBDIRS) build

clean:
	@rm -f build/*.o
	@rm -f build/*.elf
	@rm -f dingos.img

clean_compiler:
	@rm -rf compiler/*
