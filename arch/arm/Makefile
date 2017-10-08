include $(DINGOS_PATH)/Makefile_rpi2.inc

SUBDIRS = clock io serial interrupt

all: $(SUBDIRS)

$(SUBDIRS):
	$(MAKE) -C $@

.PHONY: all $(SUBDIRS)
