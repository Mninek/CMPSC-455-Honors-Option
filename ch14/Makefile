CFLAGS = -Wall -pedantic -std=c99 -O2
LIBS = -lnetpbm
all: netpbm-minimal image-io-test-0 image-io-test-1 image-io-test-2 image-io-test-3 image-io-test-4 image-io-test-5
netpbm-minimal: xmalloc.o netpbm-minimal.o
	$(CC) $^ $(LIBS) -o $@

image-io-test-0: image-io-test-0.o image-io.o image-io.h xmalloc.o
	$(CC) $^ $(LIBS) -o $@

image-io-test-1: image-io-test-1.o image-io.o image-io.h xmalloc.o
	$(CC) $^ $(LIBS) -o $@

image-io-test-2: image-io-test-2.o image-io.o image-io.h xmalloc.o
	$(CC) $^ $(LIBS) -o $@

image-io-test-3: image-io-test-3.o image-io.o image-io.h xmalloc.o
	$(CC) $^ $(LIBS) -o $@

image-io-test-4: image-io-test-4.o image-io.o image-io.h xmalloc.o
	$(CC) $^ $(LIBS) -o $@

image-io-test-5: image-io-test-5.o image-io.o image-io.h xmalloc.o
	$(CC) $^ $(LIBS) -o $@	

image-io-test-0.o: image-io-test-0.c image-io.h image-io.o xmalloc.h

image-io-test-1.o: image-io-test-1.c image-io.h image-io.o xmalloc.h

image-io-test-2.o: image-io-test-2.c image-io.h image-io.o xmalloc.h

image-io-test-3.o: image-io-test-3.c image-io.h image-io.o xmalloc.h

image-io-test-4.o: image-io-test-4.c image-io.h image-io.o xmalloc.h

image-io-test-5.o: image-io-test-5.c image-io.h image-io.o xmalloc.h

image-io.o: image-io.c array.h xmalloc.h image-io.h

netpbm-minimal.o: netpbm-minimal.c xmalloc.h array.h

xmalloc.o: xmalloc.c xmalloc.h
