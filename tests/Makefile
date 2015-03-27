CFLAGS = -g -std=gnu11 -pthread -Wall -Werror -pedantic -I. -I../ -I../include -I../utils -O2
#-fsanitize=undefined

VALGRIND_OPTS ?= -q
VALGRIND ?= $(shell which valgrind) $(VALGRIND_OPTS)

vpath %.h ../include:../utils
vpath %.c ../objects:../utils
vpath %.s ../asm

.PHONY: all
all: tests

.PHONY: tests
tests: test_lang test_map test_trie test_list

test_%: test_%.o
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)
	$(VALGRIND) ./$@
	$(RM) $@

test_lang: msg_send.o object.o type.o monitor.o method.o str.o int.o bool.o

test_trie: trie.o map.o

test_list: list.o

test_map: map.o

.PHONY: clean
clean:
	$(RM) *.o
