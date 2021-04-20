CFLAGS = -Wall -pedantic -std=c99 -O2

all: interlude evolution
interlude: interlude.o xmalloc.o read.o write.o evolution.h xmalloc.h xmalloc.o fetch-line.o fetch-line.h linked-list.o linked-list.h
	$(CC) $^ $(LIBS) -o $@

evolution: evolution.o evolution.h xmalloc.h xmalloc.o array.h read.h read.o write.h write.o linked-list.h linked-list.o world-to-eps.h world-to-eps.o fetch-line.o fetch-line.h
	$(CC) $^ $(LIBS) -o $@

evolution.o: evolution.c evolution.h xmalloc.h xmalloc.o array.h read.h read.o write.h write.o linked-list.h linked-list.o world-to-eps.h world-to-eps.o fetch-line.o fetch-line.h

world-to-eps.o: world-to-eps.c world-to-eps.h

interlude.o: read.h read.o write.h write.o evolution.h xmalloc.h xmalloc.o

read.o: read.c read.h linked-list.o linked-list.h fetch-line.o fetch-line.h

write.o: write.c write.h linked-list.h

linked-list.o: linked-list.c linked-list.h

xmalloc.o: xmalloc.c xmalloc.h

fetch-line.o: fetch-line.h fetch-line.c