CFLAGS = -g -std=c11 -Wall -pedantic -I. -I../ -I../include -I../utils -O2

vpath %.h ../include:../utils
vpath %.c ../objects:../utils
vpath %.s ../asm

.PHONY: all
all:

.PHONY: tests
tests: test_lang test_map test_trie test_list

test_lang: test_lang.o object.o str.o int.o bool.o selector.o type.o msg_send.o
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)
	valgrind -q ./$@

test_trie: test_trie.o trie.o map.o
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)
	valgrind -q ./$@

test_list: test_list.o list.o
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)
	valgrind -q ./$@

test_map: test_map.o map.o
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)
	valgrind -q ./$@

.PHONY: clean
clean:
	rm -f *.o
