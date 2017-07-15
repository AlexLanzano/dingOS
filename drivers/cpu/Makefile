include $(DINGOS_PATH)/Makefile.inc

SUBDIRS = bcm2836

all: $(SUBDIRS)

$(SUBDIRS):
	$(MAKE) -C $@

.PHONY: all $(SUBDIRS)
