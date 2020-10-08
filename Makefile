$(info Pin path is $(PINPATH))

TOP = $(shell readlink -f ..)

PREFIX ?= $(shell readlink -f $(TOP)/..)
$(info Install path is $(PREFIX))

SPECS ?= $(strip $(TOP))/gcc_scripts/specs.pincrt
$(info GCC spec file is $(SPECS))
ifeq ($(wildcard $(SPECS)),)
$(error GCC spec file does not exist)
endif

CC = gcc
SRC_DIRS = src
NO_RECURSIVE_SRC = 1
TARGET = libpin3c_missing.a

SYS_INC_DIRS = $(addprefix $(PINPATH)/, \
			   extras/stlport/include \
			   extras/libstdc++/include \
			   extras/crt/include \
			   extras/crt/include/arch-x86_64 \
			   extras/crt/include/kernel/uapi \
			   extras/crt/include/kernel/uapi/asm-x86)
LIB_DIR = $(PINPATH)/intel64/runtime/pincrt

CFLAGS = -g -O2 -D__PIN__=1 -DPIN_CRT=1 -DTARGET_IA32E -DTARGET_LINUX \
		 -funwind-tables -fno-stack-protector \
		 $(addprefix -isystem ,$(SYS_INC_DIRS))
CFLAGS += -fPIC
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti \
		   $(addprefix -isystem ,$(SYS_INC_DIRS))
LDFLAGS = -nostdlib $(addprefix -L,$(LIB_DIR))
LIBS = -lc-dynamic

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

