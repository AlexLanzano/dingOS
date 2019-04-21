DINGOS_PATH = $(shell pwd)
DINGOS_ARCH = x86_64-elf64

CC = $(DINGOS_PATH)/compiler/cross/bin/$(DINGOS_ARCH)-gcc
OBJCOPY = $(DINGOS_PATH)/compiler/cross/bin/$(DINGOS_ARCH)-objcopy
LD = $(DINGOS_PATH)/compiler/cross/bin/$(DINGOS_ARCH)-ld

CFLAGS := -Werror -Wall -Wextra -ffreestanding -nostdlib

INCLUDE_PATH := -I $(DINGOS_PATH)/include

SUBDIRS := boot
#SUBDIRS += memory

export DINGOS_PATH
export DINGOS_ARCH
export CC
export OBJCOPY
export LD
export INCLUDE_PATH
export SUBDIRS
export CFLAGS

.PHONY: all
all: build

.PHONY: build
build: $(SUBDIRS)
	$(MAKE) -C $^

.PHONY: clean
clean: $(SUBDIRS)
	$(MAKE) clean -C $^

.PHONY: compiler
compiler:
	mkdir -p compiler
	scripts/build-compiler.sh

.PHONY: clean-compiler
clean-compiler:
	rm -rf compiler/*
