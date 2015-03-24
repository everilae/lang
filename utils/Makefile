CFLAGS = -g -std=c11 -Wall -pedantic -I. -I.. -I../include -O2

.PHONY: all
all:

test_all: test_trie test_list

test_trie: CFLAGS += -DTEST=1
test_trie: trie.o
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)
	valgrind -q ./$@ a q as qw asd qwe asdf qwer b g bn gh bnm ghj
	rm -f $@

test_list: CFLAGS += -DTEST=1
test_list: list.o
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)
	valgrind -q ./$@
	rm -f $@

test_map: CFLAGS += -DTEST=1
test_map: map.o
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)
	valgrind -q ./$@
	rm -f $@

.PHONY: clean
clean:
	rm -f *.o
