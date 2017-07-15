include $(DINGOS_PATH)/Makefile.inc

SUBDIRS = cpu device gpu

all: $(SUBDIRS)

$(SUBDIRS):
	$(MAKE) -C $@

.PHONY: all $(SUBDIRS)
