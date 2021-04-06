CFLAGS = -Wall -pedantic -std=c99 -O2
LIBS = -lm
all: wavelet-test
wavelet-test: wavelet-test.o xmalloc.o wavelet.h wavelet.o 
	$(CC) $^ $(LIBS) -o $@

wavelet-test.o: wavelet-test.c wavelet.h array.h

wavelet.o: wavelet.c wavelet.h xmalloc.o array.h

xmalloc.o: xmalloc.c xmalloc.h