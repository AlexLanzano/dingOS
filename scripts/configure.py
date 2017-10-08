#! /usr/bin/python3
import sys
import os


def generate_makefile_conf():
	conf = open("Makefile.conf", "w")

	conf.write("ARCH={0}\n".format(arch))
	conf.write("CC=$(DINGOS_PATH)/compiler/cross/bin/$(ARCH)-elf-gcc\n")
	conf.write("OBJCOPY=$(DINGOS_PATH)/compiler/cross/bin/$(ARCH)-elf-objcopy\n")
	conf.write("CFLAGS=-std=gnu99 -ffreestanding -Wall -Wextra -Werror -nostdlib\n")
	conf.write("TARGET_DIR=$(DINGOS_PATH)/build/\n")
	conf.write("INCLUDE_PATH=")
	include_dirs = os.listdir("include")
	for directory in include_dirs:
		conf.write("-I$(DINGOS_PATH)/include/{0} ".format(directory))

def process_option(arg):
	global arch
	if (arg[0] != '-'):
		return 1

	if (arg[0:2] != "--"):
		option = arg[2]

	else:

		container = arg[2:].split("=", 1)
		option = container[0]
		if (len(container) > 1):
			value = container[1]

		if (option == "arch"):
			arch = value

def main():
	for arg in sys.argv:
		process_option(arg)

	generate_makefile_conf()

main()
