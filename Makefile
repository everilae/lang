CFLAGS = -g -std=c11 -Wall -pedantic -I. -Iinclude -O2

vpath %.h include
vpath %.c objects
vpath %.s asm

.PHONY: all
all:

test_all: test_lang

test_lang: test.o object.o str.o int.o bool.o selector.o type.o msg_send.o
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)
	valgrind -q ./$@
	rm -f $@

.PHONY: clean
clean:
	rm -f *.o
