#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "fetch-line.h"
static char *trim_line(char *s);
char *fetch_line(char *buf, int buflen, FILE *stream, int *lineno);

static char *trim_line(char *s){
    int done = 0;
    int leadWhite = 0;
    while (!done){
        if (isspace((unsigned char)s[leadWhite])){
            s++; 
            leadWhite++;
        } else {
            done = 1;
        }
    }
    done = 0;
    int chars = 0;
    while (!done){
        if (s[leadWhite + chars] == '#'){
            s[leadWhite + chars] = '\0';
            done = 0;
        }

        if (s[leadWhite + chars] == '\0'){
            done = 1;
        } else {
            chars++;
        }
    }
    done = 0;
    while (!done){
        if ((unsigned char)isspace(s[leadWhite + chars])){
            s[leadWhite + chars] = '\0';
            chars--;
        } else {
            done = 1;
        }
    }
    char *t = (char*)malloc(sizeof(char) * (chars-leadWhite));
    int i;
    int j = 0;
    for (i = leadWhite; i < chars; i++){
        t[j] = s[i];
        j++;
    }
    return t;
}

char *fetch_line(char *buf, int buflen, FILE *stream, int *lineno) {
    char *s;
    if (fgets(buf, buflen, stream) == NULL)
        return NULL;
    ++*lineno;
    if (buf[strlen(buf) - 1] != '\n') {
        fprintf(stderr, "*** reading error: input line %d too "
        "long for %s's buf[%d]\n",
        *lineno, __func__, buflen);
        exit(EXIT_FAILURE);
    }
    s = trim_line(buf);
    if (*s != '\0')
        return s;
    else 
        return fetch_line(buf, buflen, stream, lineno);
}