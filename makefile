CC=gcc
CFLAGS=-Wall -Wextra -std=c99

tree: tree.o
	$(CC) $(CFLAGS) tree.o -o tree

tree.o: tree.c
	$(CC) $(CFLAGS) -c tree.c

clean:
	rm -f tree.o tree
