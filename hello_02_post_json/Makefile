# Copyright (c) 2012 The Native Client Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

#
# GNU Make based build file.  For details on GNU Make see:
#   http://www.gnu.org/software/make/manual/make.html
#

#
# Project information
#
# These variables store project specific settings for the project name
# build flags, files to copy or install.  In the examples it is typically
# only the list of sources and project name that will actually change and
# the rest of the makefile is boilerplate for defining build rules.
#
PROJECT:=hello
CXX_SOURCES=mariner.cpp hello.cpp
C_SOURCES=../nacl_single_instance/nacl.c ../nacl_single_instance/nacl_settings.c
DDLT=~/DDLParser/ddlt/ddlt
INCLUDE_DIRS=../nacl_single_instance
LIBRARY_DIRS :=
LIBRARIES :=ppapi_gles2 ppapi_cpp ppapi

#
# Get pepper directory for toolchain and includes.
#
# If PEPPER_ROOT is not set, then assume it can be found a two directories up,
# from the default example directory location.
#
THIS_MAKEFILE:=$(abspath $(lastword $(MAKEFILE_LIST)))
NACL_SDK_ROOT?=$(abspath $(dir $(THIS_MAKEFILE))../..)

# Project Build flags
# WARNINGS:=-Wno-long-long -Wall -Wswitch-enum -pedantic -Werror
WARNINGS:=-Wno-long-long -Wall -Wswitch-enum -pedantic
CXXFLAGS:=-pthread -std=gnu++98 $(WARNINGS)
CCFLAGS:=-pthread -std=c99 $(WARNINGS)
LDFLAGS:=-pthread

# Add paths
CXXFLAGS += $(foreach includedir,$(INCLUDE_DIRS),-I$(includedir))
CCFLAGS += $(foreach includedir,$(INCLUDE_DIRS),-I$(includedir))
LDFLAGS += $(foreach librarydir,$(LIBRARY_DIRS),-L$(librarydir))
LDFLAGS += $(foreach library,$(LIBRARIES),-l$(library))

#
# Compute tool paths
#
#
OSNAME:=$(shell python $(NACL_SDK_ROOT)/tools/getos.py)
TC_PATH:=$(abspath $(NACL_SDK_ROOT)/toolchain/$(OSNAME)_x86_newlib)
CXX:=$(TC_PATH)/bin/i686-nacl-g++
CC:=$(TC_PATH)/bin/i686-nacl-gcc
LINK:=$(TC_PATH)/bin/i686-nacl-g++

#
# Disable DOS PATH warning when using Cygwin based tools Windows
#
CYGWIN ?= nodosfilewarning
export CYGWIN

# Declare the ALL target first, to make the 'all' target the default build
all: $(PROJECT)_x86_32.nexe $(PROJECT)_x86_64.nexe

mariner.h: $(DDLT) mariner.ddl
	$(DDLT) -i mariner.ddl -t nacl_hpp -o mariner.h

mariner.cpp: $(DDLT) mariner.ddl mariner.h JsonWriteScope.h
	$(DDLT) -i mariner.ddl -t nacl_cpp -I mariner.h -I JsonWriteScope.h -o mariner.cpp

# Define 32 bit compile and link rules for C++ sources
x86_32_CXX_OBJS:=$(patsubst %.cpp,%_32.o,$(CXX_SOURCES))
x86_32_C_OBJS:=$(patsubst %.c,%_32.o,$(C_SOURCES))
x86_32_OBJS:= $(x86_32_CXX_OBJS) $(x86_32_C_OBJS)
$(x86_32_CXX_OBJS) : %_32.o : %.cpp $(THIS_MAKE)
	$(CXX) -o $@ -c $< -m32 -O0 -g $(CXXFLAGS)
$(x86_32_C_OBJS) : %_32.o : %.c $(THIS_MAKE)
	$(CC) -o $@ -c $< -m32 -O0 -g $(CCFLAGS)
$(PROJECT)_x86_32.nexe : $(x86_32_OBJS)
	$(LINK) -o $@ $^ -m32 -O0 -g $(LDFLAGS)

# Define 64 bit compile and link rules for C++ sources
x86_64_CXX_OBJS:=$(patsubst %.cpp,%_64.o,$(CXX_SOURCES))
x86_64_C_OBJS:=$(patsubst %.c,%_64.o,$(C_SOURCES))
x86_64_OBJS:= $(x86_64_CXX_OBJS) $(x86_64_C_OBJS)
$(x86_64_CXX_OBJS) : %_64.o : %.cpp $(THIS_MAKE)
	$(CXX) -o $@ -c $< -m64 -O0 -g $(CXXFLAGS)
$(x86_64_C_OBJS) : %_64.o : %.c $(THIS_MAKE)
	$(CC) -o $@ -c $< -m64 -O0 -g $(CCFLAGS)
$(PROJECT)_x86_64.nexe : $(x86_64_OBJS)
	$(LINK) -o $@ $^ -m64 -O0 -g $(LDFLAGS)

# Define a phony rule so it always runs, to build nexe and start up server.
.PHONY: RUN 
RUN: all
	python ../httpd.py


.PHONY: clean
clean:
	rm -f $(x86_32_OBJS) $(x86_64_OBJS)
	rm -f *.nexe
	rm -f *.orig

.PHONY: clean-ddl
clean-ddl:
	rm -f mariner.cpp
	rm -f mariner.h

