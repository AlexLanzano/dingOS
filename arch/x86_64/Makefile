SUBDIRS := $(wildcard */.)

all: $(SUBDIRS)

$(SUBDIRS):
	@$(MAKE) -C $@

.PHONY: $(SUBDIRS)
