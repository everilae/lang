CFLAGS = -g -std=c11 -Wall -pedantic -I. -Iinclude -Iutils -O2

vpath %.h include:utils
vpath %.c objects:utils
vpath %.s asm

.PHONY: all
all:

.PHONY: tests
tests:
	$(MAKE) -C tests

.PHONY: clean
clean:
	rm -f *.o
	$(MAKE) -C tests clean
