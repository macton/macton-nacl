# GNU MAKE Makefile for PDCurses library - WIN32 Cygnus GCC
#
# Usage: make -f [path\]gccwin32.mak [DEBUG=Y] [DLL=Y] [WIDE=Y] [UTF8=Y] [tgt]
#
# where tgt can be any of:
# [all|demos|pdcurses.a|testcurs.exe...]

O = o

ifndef PDCURSES_SRCDIR
	PDCURSES_SRCDIR = ..
endif

include $(PDCURSES_SRCDIR)/version.mif
include $(PDCURSES_SRCDIR)/libobjs.mif

osdir		= $(PDCURSES_SRCDIR)/nacl
PDCURSES_NACL_H	= 

CC		= gcc
OSNAME          := $(shell python $(NACL_SDK_ROOT)/tools/getos.py)
TC_PATH         := $(abspath $(NACL_SDK_ROOT)/toolchain/$(OSNAME)_x86_newlib)
CC              := $(TC_PATH)/bin/i686-nacl-gcc
LINK            := $(TC_PATH)/bin/i686-nacl-gcc
LIBEXE          := $(TC_PATH)/bin/i686-nacl-ar
STRIP           := $(TC_PATH)/bin/i686-nacl-strip


ifeq ($(DEBUG),Y)
	CFLAGS  = -g -Wall -DPDCDEBUG
	LDFLAGS = -g
else
	CFLAGS  = -O2 -Wall
	LDFLAGS =
endif


CFLAGS += -I$(PDCURSES_SRCDIR)
CFLAGS += -DNACL -DPDC_PLATFORM=\"nacl_x86_32\"

LIBFLAGS  = rcv
LIBCURSES = pdcurses_x86_32.a
LIBDEPS   = $(LIBOBJS) $(PDCOBJS)
CLEAN     = *.a

.PHONY: all libs clean demos dist

all:	libs demos

libs:	$(LIBCURSES)

clean:
	-rm -f *.o
	-rm -f $(DEMOS)
	-rm -f $(CLEAN)


$(LIBCURSES) : $(LIBDEPS)
	$(LIBEXE) $(LIBFLAGS) $@ $?
	-cp pdcurses.a panel.a

$(LIBOBJS) $(PDCOBJS) : $(PDCURSES_HEADERS)
$(PDCOBJS) : $(PDCURSES_NACL_H)

DEMOS		= firework newdemo ptest rain testcurs tuidemo worm xmas

demos:	$(DEMOS)
	$(STRIP) $(DEMOS)

panel.o : $(PANEL_HEADER)
terminfo.o: $(TERM_HEADER)

$(LIBOBJS) : %.o: $(srcdir)/%.c
	$(CC) -c $(CFLAGS) $<

$(PDCOBJS) : %.o: $(osdir)/%.c
	$(CC) -c $(CFLAGS) $<

$(DEMOS) : $(PDCURSES_CURSES_H) $(LIBCURSES)
tui.o tuidemo.o : $(PDCURSES_HEADERS)

firework: $(demodir)/firework.c
	$(CC) $(CFLAGS) -o$@ $< $(LIBCURSES)

newdemo: $(demodir)/newdemo.c
	$(CC) $(CFLAGS) -o$@ $< $(LIBCURSES)

ptest: $(demodir)/ptest.c
	$(CC) $(CFLAGS) -o$@ $< $(LIBCURSES)

rain: $(demodir)/rain.c
	$(CC) $(CFLAGS) -o$@ $< $(LIBCURSES)

testcurs: $(demodir)/testcurs.c
	$(CC) $(CFLAGS) -o$@ $< $(LIBCURSES)

tuidemo: tuidemo.o tui.o
	$(LINK) $(LDFLAGS) -o$@ tuidemo.o tui.o $(LIBCURSES)

worm: $(demodir)/worm.c
	$(CC) $(CFLAGS) -o$@ $< $(LIBCURSES)

xmas: $(demodir)/xmas.c
	$(CC) $(CFLAGS) -o$@ $< $(LIBCURSES)

tui.o: $(demodir)/tui.c $(demodir)/tui.h
	$(CC) -c $(CFLAGS) -I$(demodir) -o$@ $<

tuidemo.o: $(demodir)/tuidemo.c
	$(CC) -c $(CFLAGS) -I$(demodir) -o$@ $<
