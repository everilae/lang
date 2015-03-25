CFLAGS = -g -std=gnu11 -pthread -Wall -Werror -pedantic -I. -Iinclude -Iutils -O2

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
	$(RM) *.o
	$(MAKE) -C tests clean
