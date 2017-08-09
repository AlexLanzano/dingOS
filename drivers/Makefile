include $(DINGOS_MAKEFILE_INCLUDE)

SUBDIRS = cpu device gpu

rpi2: $(SUBDIRS)

x86: $(SUBDIRS)

$(SUBDIRS):
	$(MAKE) $(RULE) -C $@

.PHONY: x86 rpi2 $(SUBDIRS)
