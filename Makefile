$(info Pin path is $(PINPATH))

PREFIX = $(shell readlink -f ../..)
$(info Install path is $(PREFIX))

SPECS = $(strip $(PREFIX))/src/specs.pincrt
$(info GCC spec file is $(SPECS))
ifeq ($(wildcard $(SPECS)),)
$(error GCC spec file does not exist)
endif

CC = gcc
SRC_DIRS = src
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
	cp $(TARGET) $(INSTALL_DIR)

uninstall:
	rm -f $(INSTALL_DIR)/$(TARGET)

.PHONY: install uninstall

