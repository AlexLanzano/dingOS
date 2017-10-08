include $(DINGOS_CONF)

SUBDIRS := $(wildcard */.)

all: $(SUBDIRS)

$(SUBDIRS):
	@$(MAKE) -C $@

.PHONY: $(SUBDIRS)
