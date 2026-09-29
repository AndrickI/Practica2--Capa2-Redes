CC=gcc
CFLAGS=-Wall

LIBS=-lpcap


all: emisor receptor


emisor: src/emisor.c
	$(CC) $(CFLAGS) src/emisor.c -o emisor $(LIBS)


receptor: src/receptor.c
	$(CC) $(CFLAGS) src/receptor.c -o receptor $(LIBS)


clean:
	rm -f emisor receptor
