CFLAGS += -std=c99 -pedantic -Wall -O2
LDLIBS += -lc
PREFIX ?= /usr/local

.PHONY: default all clean install uninstall

default: all

all: bfc

bfc: bff4.o
	@cc $(LDFLAGS) $(LDLIBS) -o $@ $<
	@echo linking...

bff4.o: bff4.c
	@cc $(CFLAGS) -c -o $@ $<
	@echo compiling

clean:
	@rm bfc bff4.o

install: bfc
	@install bfc $(PREFIX)/bin/bfc

uninstall:
	@rm $(PREFIX)/bin/bfc
