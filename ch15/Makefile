CFLAGS = -Wall -pedantic -std=c99 -O2
LIBS = -lnetpbm -lm
all: image-analysis

image-analysis: image-analysis.o xmalloc.o wavelet.h wavelet.o array.h image-io.o image-io.h 
	$(CC) $^ $(LIBS) -o $@

image-analysis.o: image-analysis.c array.h image-io.h wavelet.h image-io.o

image-io.o: image-io.c array.h xmalloc.h image-io.h

wavelet.o: wavelet.c wavelet.h xmalloc.o array.h

malloc.o: xmalloc.c xmalloc.h