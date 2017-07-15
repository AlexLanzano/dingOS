include $(DINGOS_PATH)/Makefile.inc

SUBDIRS = clock io serial

all: $(SUBDIRS)

$(SUBDIRS):
	$(MAKE) -C $@

.PHONY: all $(SUBDIRS)
