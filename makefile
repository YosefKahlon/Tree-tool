CC=gcc
CFLAGS=-Wall

stree: stree.c
	$(CC) $(CFLAGS) -o stree stree.c


.PHONY: clean
clean:
	rm -f stree
