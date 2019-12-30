# Makefile for alstv/findpath

#CC = gcc
CC = i686-w64-mingw32-gcc 

CFLAGS = -g3 -O0 -Wall -Wextra -DDEMOPATH

ARGS =

INSTALDIR = /usr/local/bin

all: findpath

run:
	./findpath $(ARGS)

install: findpath
	cp findpath $(INSTALDIR)/

uninstall: $(INSTALDIR)/alstv/findpath
	rm -i $(INSTALDIR)/alstv/findpath

findpath: findpath.o

findpath.o: findpath.c

.PHONY: clean
clean:
	$(RM) *.o
	$(RM) *.exe
	$(RM) *.asm
	$(RM) *.map
	$(RM) *.stackdump
	$(RM) *.core
