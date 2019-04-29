###############################################################################
# Copyright (c) 2019, Mingyu Gao
# All rights reserved.
#
# General Makefile for C/C++.
#
# How to use: create a makefile, overwrite variables, and include this file.
#
# Example:
# ---
# TARGET = libfoo.so
# SRC_DIRS = src
# LIBS = -lz
#
# -include makefile.inc
# ---
#
###############################################################################

# Assume this file exists at the top directory.
TOP_DIR := $(realpath $(dir $(word $(words $(MAKEFILE_LIST)), $(MAKEFILE_LIST))))

#---------------------------------- Settings ---------------------------------#
#                              TO BE OVERWRITTEN                              #

# Input and output.
TARGET   ?= $(strip $(TOP_DIR))/a.out
SRC_DIRS ?= $(strip $(TOP_DIR))/src
INC_DIRS ?= $(strip $(TOP_DIR))/include

# User-defined flags.
CFLAGS  ?=
LDFLAGS ?=
LIBS    ?=

# Command line switches.
D ?= 0  # debug mode?
V ?= 0  # verbose mode?

# Info.
$(info Top directory = $(TOP_DIR))
$(info Source directories = $(SRC_DIRS))
$(info Target = $(TARGET))

#------------------------ Generic variables and rules ------------------------#
#                            NO NEED TO EDIT BELOW                            #

# Figure out target type: exe, .a, or .so?
NLIB_TARGET = $(patsubst %.a,%,$(patsubst %.so,%,$(TARGET)))  # remove .a/.so suffix
A_TARGET    = $(strip $(NLIB_TARGET)).a
SO_TARGET   = $(strip $(NLIB_TARGET)).so
ifeq ($(TARGET),$(A_TARGET))
IS_A = 1
else  # neq($(TARGET),$(A_TARGET))
IS_A = 0
endif  # ($(TARGET),$(A_TARGET))
ifeq ($(TARGET),$(SO_TARGET))
IS_SO = 1
else  # neq($(TARGET),$(SO_TARGET))
IS_SO = 0
endif  # ($(TARGET),$(SO_TARGET))

# Commands.
CC    ?= gcc
CXX   ?= g++
AR    ?= ar
RM    ?= rm
ifeq ($(V),1)
V_CC   = $(CC)
V_CXX  = $(CXX)
V_AR   = $(AR)
else  # !$(V)
V_CC   = @$(CC)
V_CXX  = @$(CXX)
V_AR   = @$(AR)
endif  # $(V)

# Flags.
CC_FLAGS   = $(CFLAGS_LANG) $(CFLAGS_OPT) $(CFLAGS_SHD) $(CFLAGS)
CXX_FLAGS  = $(CXXFLAGS_LANG) $(CXXFLAGS_OPT) $(CXXFLAGS_SHD) $(CXXFLAGS)
LK_FLAGS   = $(LDFLAGS_SHD) $(LDFLAGS) $(LIBS)
CFLAGS_LANG   := -Wall -Wextra -pedantic
CXXFLAGS_LANG := $(CFLAGS_LANG) -std=c++11
ifeq ($(D),1)
CFLAGS_OPT    := -g -fkeep-inline-functions
else  # !$(D)
CFLAGS_OPT    := -O3
ifneq ($(IS_A),1)
CFLAGS_OPT    := -flto
endif  # $(IS_A)
endif  # $(D)
CXXFLAGS_OPT  := $(CFLAGS_LANG)
ifeq ($(IS_SO),1)
CFLAGS_SHD    := -fPIC
endif  # $(IS_SO)
CXXFLAGS_SHD  := $(CFLAGS_SHD)
ifeq ($(IS_SO),1)
LDFLAGS_SHD := -shared
endif  # $(IS_SO)

# Extensions.
CC_EXTS  ?= .c .cc .C
CXX_EXTS ?= .cpp .cxx .c++
SRC_EXTS  = $(CC_EXTS) $(CXX_EXTS)
OBJ_EXT  := .o
DEP_EXT  := .d

# Directories and files.
DIRS := $(foreach DIR,$(SRC_DIRS),$(shell find $(DIR) -type d -print))  # recursively find all subdirectories in src dir
SRCS := $(foreach EXT,$(SRC_EXTS),$(foreach DIR,$(DIRS),$(wildcard $(DIR)/*$(EXT))))  # find all src at each dir with each ext
OBJS := $(filter %$(OBJ_EXT),$(foreach EXT,$(SRC_EXTS),$(SRCS:$(EXT)=$(OBJ_EXT))))  # replace src ext with obj ext
DEPS := $(OBJS:$(OBJ_EXT)=$(DEP_EXT))  # replace obj ext with dep ext

# Rules.

all: $(TARGET)


$(NLIB_TARGET): $(OBJS)
	@echo "  LD " $@
	$(V_CC) $(CC_FLAGS) -o $@ $^ $(LK_FLAGS)

$(A_TARGET): $(OBJS)
	@echo "  AR " $@
	$(V_AR) crs $@ $^

$(SO_TARGET): $(OBJS)
	@echo "  LD " $@
	$(V_CC) $(CC_FLAGS) -o $@ $^ $(LK_FLAGS)

$(CC_EXTS:=$(OBJ_EXT)):
	@echo "  CC " $@
	$(V_CC) $(CC_FLAGS) $(addprefix -I,$(INC_DIRS)) -c -o $@ $< -MMD -MP

$(CXX_EXTS:=$(OBJ_EXT)):
	@echo "  CXX " $@
	$(V_CXX) $(CXX_FLAGS) $(addprefix -I,$(INC_DIRS)) -c -o $@ $< -MMD -MP

clean:
	$(RM) -f $(TARGET)
	$(RM) -f $(OBJS) $(DEPS)
	$(RM) -f $(addsuffix /*~,$(DIRS))

.PHONY: clean all

-include $(DEPS)

