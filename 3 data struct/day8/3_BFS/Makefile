CC=gcc
CFLAGS=-Wall -g -O2
OBJS=BFS

$(OBJS):BFS.o linkqueue.o
	$(CC) $^ -o $@

%*.o:%*.c
	$(CC) $(CFLAGS) $< -o $@

.PHONY:
	clean

clean:
	$(RM) a.out $(OBJS) *.o -rf
