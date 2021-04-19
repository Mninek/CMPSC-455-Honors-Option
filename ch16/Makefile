CFLAGS = -Wall -pedantic -std=c99 -O2

all: test1 test2 test3 test4 test5 test6 test7

test7: test7.o linked-list.h linked-list.o xmalloc.o

test6: test6.o linked-list.h linked-list.o xmalloc.o array.h

test5: test5.o linked-list.h linked-list.o xmalloc.o array.h

test4: test4.o linked-list.h linked-list.o xmalloc.o

test3: test3.o linked-list.h linked-list.o xmalloc.o

test2: test2.o linked-list.h linked-list.o xmalloc.o

test1: test1.o linked-list.h linked-list.o xmalloc.o

test7.o: test7.c linked-list.o xmalloc.o xmalloc.h

test6.o: test6.c linked-list.o xmalloc.o xmalloc.h

test5.o: test5.c linked-list.o xmalloc.o xmalloc.h

test4.o: test4.c linked-list.o xmalloc.o xmalloc.h

test3.o: test3.c linked-list.o xmalloc.o xmalloc.h

test2.o: test2.c linked-list.o xmalloc.o xmalloc.h

test1.o: test1.c linked-list.o xmalloc.o xmalloc.h

linked-list.o: linked-list.c linked-list.h

xmalloc.o: xmalloc.c xmalloc.h