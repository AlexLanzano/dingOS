DINGOS_PATH = $(shell pwd)
DINGOS_ARCH = x86_64

CC = $(DINGOS_PATH)/compiler/cross/bin/gcc
OBJCOPY = $(DINGOS_PATH)/compiler/cross/bin/objcopy
LD = $(DINGOS_PATH)/compiler/cross/bin/ld

CFLAGS := -Werror
CFLAGS += -Wall
CFLAGS += -Wextra
CFLAGS += -ffreestanding
CFLAGS += -nostdlib

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

.PHONY: all
all: build

.PHONY: clean
clean: $(SUBDIRS)
       $(MAKE) clean -C $^

.PHONY: compiler
compiler:
       mkdir -p compiler
       scripts/build-compiler.sh

.PHONY: build
build: $(SUBDIRS)
       $(MAKE) -C $^
