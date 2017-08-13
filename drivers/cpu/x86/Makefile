include $(DINGOS_MAKEFILE_INCLUDE)

SUBDIRS = vga

all: $(SUBDIRS)

$(SUBDIRS):
	$(MAKE) -C $@

.PHONY: all $(SUBDIRS)
