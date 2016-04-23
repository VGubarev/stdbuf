CC = gcc
CFLAGS = -g
RM = rm
TARGETS = stdbuf libmstdbuf.so test

all: $(TARGETS)

stdbuf: stdbuf.c
	$(CC) $(CFLAGS) stdbuf.c -o $@
test: 
	$(CC) $(CFLAGS) test.c -o $@
libmstdbuf.so: libmstdbuf.o
	$(CC) -shared libmstdbuf.o -o $@
libmstdbuf.o: libmstdbuf.c
	$(CC) -c -Wall -Werror -fpic libmstdbuf.c -o $@
clean:
	$(RM) -f *.o $(TARGETS) 
