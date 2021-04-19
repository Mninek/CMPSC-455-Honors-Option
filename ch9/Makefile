CFLAGS = -Wall -pedantic -std=c99 -O2

all: fetch-line-demo
fetch-line-demo: fetch-line.h fetch-line.o fetch-line-demo.o
	$(CC) $^ $(LIBS) -o $@

fetch-line-demo.o: fetch-line-demo.c fetch-line.h fetch-line.o

fetch-line.o: fetch-line.h fetch-line.c