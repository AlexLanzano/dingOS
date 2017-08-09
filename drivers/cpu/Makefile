ifdef DINGOS_RPI2
include $(DINGOS_PATH)/Makefile_rpi2.inc
else ifdef DINGOS_X86
include $(DINGOS_PATH)/Makefile_x86.inc
endif

SUBDIRS_RPI2 = bcm2836
SUBDIRS_X86 = x86

rpi2: $(SUBDIRS_RPI2)
x86: $(SUBDIRS_X86)

$(SUBDIRS_RPI2):
	$(MAKE) -C $@
$(SUBDIRS_X86):
	$(MAKE) -C $@

.PHONY: rpi2 x86 $(SUBDIRS_RPI2) $(SUBDIRS_X86)
