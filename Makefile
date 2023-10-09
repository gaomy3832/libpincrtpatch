$(info Pin path is $(PINPATH))

TOP = $(shell readlink -f ..)

PREFIX ?= $(shell readlink -f $(TOP)/..)
$(info Install path is $(PREFIX))

SPECS ?= $(strip $(TOP))/gcc_scripts/specs.pincrt
$(info GCC spec file is $(SPECS))
ifeq ($(wildcard $(SPECS)),)
$(error GCC spec file does not exist)
endif

CC = gcc -specs=$(SPECS) -nostdlib
SRC_DIRS = src
NO_RECURSIVE_SRC = 1
TARGET = libpincrtpatch.so

-include makefile.inc

INSTALL_DIR = $(strip $(PREFIX))/lib

install:
	mkdir -p $(INSTALL_DIR)
	cp $(TARGET) $(INSTALL_DIR)

uninstall:
	rm -f $(INSTALL_DIR)/$(TARGET)

.PHONY: install uninstall

# additional flags for tz
src/mktime.o: CFLAGS += -Wno-address -Wno-unused-parameter

LDFLAGS += -Wno-maybe-uninitialized

