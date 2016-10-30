CC=gcc
CFLAGS=-Wall -g -O2
OBJS=main

$(OBJS):main.o linkqueue.o seqstack.o
	$(CC) $^ -o $@

%*.o:%*.c
	$(CC) $(CFLAGS) $< -o $@

.PHONY:
	clean

clean:
	$(RM) a.out $(OBJS) *.o -rf
