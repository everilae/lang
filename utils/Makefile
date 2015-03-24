CFLAGS = -g -std=c11 -Wall -pedantic -I. -I.. -I../include -O2

.PHONY: all
all:

.PHONY: test_all
test_all: test_map test_trie test_list

test_trie: test_trie.o trie.o map.o
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)
	valgrind -q ./$@ a q as qw asd qwe asdf qwer b g bn gh bnm ghj za foo zz bar yya jep yzb jop
	rm -f $@

test_list: CFLAGS += -DTEST=1
test_list: list.o
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)
	valgrind -q ./$@
	rm -f $@

test_map: test_map.o map.o
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)
	valgrind -q ./$@
	rm -f $@

.PHONY: clean
clean:
	rm -f *.o
