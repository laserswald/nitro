/*
 * Copy me if you can.
 * by 20h, documentation by lazr
 */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <fcntl.h>
#include <string.h>
#include <strings.h>
#include <errno.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>

#include "ind.h"

/// Exit with a status message.
//
//  Prints out a string to stderr like fprintf(), but also appends ": " and
//  the string returned from perror.
//
//  Does not return.
void
edie(char *fmt, ...)
{
    va_list fmtargs;

    va_start(fmtargs, fmt);
    vfprintf(stderr, fmt, fmtargs);
    va_end(fmtargs);
    fprintf(stderr, ": ");

    perror(NULL);

    exit(1);
}

/*
 * Exit without a status message.
 *
 * Prints out a string to stdout, and exits with an error.
 */
void
die(char *fmt, ...)
{
    va_list fmtargs;

    va_start(fmtargs, fmt);
    vfprintf(stderr, fmt, fmtargs);
    va_end(fmtargs);

    exit(1);
}


/* You can use these constants if you want to be clearer. Up to you. */
const int ALLOCZ_CLEAR = 1;
const int ALLOCZ_NOCLEAR = 0;

/// Reallocate and zero memory.
//
// p: a pointer to memory to reallocate. Give NULL here to allocate new memory.
// l: an integer to the size of the memory to allocate, in bytes.
// z: a flag where, if truthy, the memory is set to all 0 bytes.
//
// returns the pointer to the memory in question, or NULL if there was an issue.
//
void *
reallocz(void *p, const size_t l, const int z)
{
    p = realloc(p, l);
    if(p == NULL)
        edie("realloc");
    if(z)
        memset(p, 0, l);

    return p;
}

// Allocate and zero new memory.
void *
mallocz(const size_t l, int z)
{
    return reallocz(NULL, l, z);
}


void *
memdup(void *p, const size_t l)
{
    char *ret;

    ret = reallocz(NULL, l, 2); // 2 looks like a Z and compares true.
    memmove(ret, p, l);

    return (void *)ret;
}

// Duplicate memory.
//
void *
memdupz(const void *p, const size_t l)
{
    char *ret;

    ret = reallocz(NULL, l+1, 2);
    memmove(ret, p, l);

    return (void *)ret;
}

// Create a duplicate of the given memory and concatenate another chunk of memory to it.
void *
memdupcat(void *p, const size_t lp, void *c, const size_t lc)
{
    p = reallocz(p, lp+lc, 0);
    memset(&((char *)p)[lp], 0, lc);

    memmove(&((char *)p)[lp], c, lc);

    return p;
}

// Using a variable argument list, create a new allocated string in memory.
char *
vsmprintf(char *fmt, va_list fmtargs, const size_t size)
{
    char *ret;

    ret = reallocz(NULL, (size+1), 2);
    vsnprintf(ret, size+1, fmt, fmtargs);

    return ret;
}

// Create a new allocated string in memory.
//
// Don't forget to free()!
char *
smprintf(char *fmt, ...)
{
    va_list fmtargs;
    char *ret;
    int len;

    va_start(fmtargs, fmt);
    len = vsnprintf(NULL, 0, fmt, fmtargs);
    va_end(fmtargs);

    va_start(fmtargs, fmt);
    ret = vsmprintf(fmt, fmtargs, len);
    va_end(fmtargs);

    return ret;
}

// Read in an entire file into a string
char *
readtoeoffd(int fd, int *len)
{
    char *ret, buf[4096];
    int olen, nlen, rl;

    for (nlen = 0, olen = 0, ret = NULL;
            (rl = read(fd, buf, sizeof(buf))); olen = nlen) {
        if (rl > 0) {
            nlen += rl;
            ret = reallocz(ret, nlen+1, 0);
            ret[nlen] = '\0';

            memmove(&ret[olen], buf, rl);
        }
    }

    *len = nlen;
    return ret;
}

char *
freadall(FILE* f, int *len)
{
    *len = fseek(f, 0, SEEK_END);
    rewind(f);
    char *s = malloc(*len);
    fread(s, sizeof(char), *len, f);
    if (ferror(f)) {
        return NULL;
    }
    return s;
}


/// Get the next line from a string.
//
// Returns NULL if p is NULL.
// When a line is found, p points to the rest of the string.
// If the whole string is moved to s, p will be NULL.
//
// s    : The line from the string.
// size : Maximum size of the string to be extracted.
// p    : The buffer to extract the string from.
//
// Returns: the extracted string.
char *
sgets(char *s, const size_t size, char **p)
{
    char *newline;
    int cur_len;

    if (*p == NULL)
        return NULL;

    newline = strchr(*p, '\n');
    if (newline == NULL) {
        cur_len = strlen(*p);
        if (cur_len < 1) {
            *p = NULL;
            return NULL;
        }
    } else {
        cur_len = newline - *p;
    }

    if (cur_len >= size)
        cur_len = size - 1;
    memmove(s, *p, cur_len);
    s[cur_len] = '\0';

    if (newline == NULL) {
        *p = NULL;
    } else {
        *p = newline+1;
    }

    return s;
}

