#include <stdio.h>
#include "xmalloc.h"

//MOST CODE BELOW IS COPIED FROM TEXTBOOK CHAPTER 7 
//I WAS TOLD TO DO THIS
void*malloc_or_exit(size_t nbytes,const char*file,intline)
{
    void *x;
    //fail if we try to allocate 0 bytes.
    if (nbytes == 0){
        fprintf(stderr, "%s:line %d: Cannot allocate 0 bytes\n",
                file, line);
        exit(EXIT_FAILURE);
    }
    if ((x = malloc(nbytes)) == NULL) {
        fprintf(stderr, "%s:line %d: malloc() of %zu bytes failed\n",
                file, line, nbytes);
        exit(EXIT_FAILURE);
    } else
        return x;
}