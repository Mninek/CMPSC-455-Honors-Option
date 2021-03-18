CC = gcc
CFLAGS = -Wall -pedantic -std=c99 -O2
LIBS = -lnetpbm
netpbm-minimal: xmalloc.o netpbm-minimal.o
    $(cc) $^ $(LIBS) -o $@