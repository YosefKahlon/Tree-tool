CC=gcc
CFLAGS=-Wall

tree: tree.o
	$(CC) $(CFLAGS) tree.o -o tree

tree.o: tree.c
	$(CC) $(CFLAGS) -c tree.c

stree: stree.c
	$(CC) $(CFLAGS) -o stree stree.c


.PHONY: clean
clean:
	rm -f tree.o tree stree
