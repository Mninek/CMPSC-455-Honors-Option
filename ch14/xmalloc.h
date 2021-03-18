#ifndef H_XMALLOC_H
#define H_XMALLOC_H
#include <stdlib.h>
void *malloc_or_exit(size_t nbytes,const char *file, intline);
#define xmalloc(nbytes)  malloc_or_exit((nbytes), __FILE__, __LINE__)
#endif /*H_XMALLOC_H*/

//above is copied from textbook chapter 7
//was told to do this