export DINGOS_ARCH = x86_64
export DINGOS_PATH := $(shell pwd)
KERNEL_PATH := $(DINGOS_PATH)/kernel/$(DINGOS_ARCH)

all: build_kernel

build_kernel:
	$(MAKE) -C $(KERNEL_PATH)

.PHONY: compiler
compiler:
	mkdir -p compiler
	scripts/build-compiler.sh $(DINGOS_ARCH)

.PHONY: clean
clean: clean-kernel
	rm -f *.img

clean-kernel:
	$(MAKE) -C $(KERNEL_PATH) clean

clean-compiler:
	rm -rf compiler/*


# Debug Targets
run:
	qemu-system-x86_64 -hda dingos-x86_64.img -d in_asm

run-debug:
	qemu-system-x86_64 -s -S -hda dingos-x86_64.img -d in_asm,guest_errors,cpu_reset

run-debug-boot:
	qemu-system-i386 -s -S -hda dingos-x86_64.img -d in_asm,guest_errors -nographic

gdb:
	gdb -ex "file kernel/x86_64/kernel.elf" -ex "set arch i386:x86-64" -ex "target remote localhost:1234"

gdb-boot:
	gdb -ex "file kernel/x86_64/boot.elf" -ex "set arch i386" -ex "target remote localhost:1234"
