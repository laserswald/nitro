/*
 * Copy me if you can.
 * by 20h
 */

#ifndef __IND_H__
#define __IND_H__

#include <stdio.h>
#include <stdarg.h>
#include <time.h>

/* A collection of useful utility functions that honestly should be in 
 * the standard library anyways.
 */

// Error functions
void die(char *fmt, ...);
void edie(char *fmt, ...);

// Memory functions
void *reallocz(void *p, const size_t l, const int z);
void *mallocz(const size_t l, int z);
void *memdup(void *p, const size_t l);
void *memdupz(void *p, const size_t l);
void *memdupcat(void *p, const size_t lp, void *c, const size_t lc);

// String functions
char *vsmprintf(char *fmt, va_list fmtargs, const size_t size);
char *smprintf(char *fmt, ...);
char *readtoeoffd(int fd, int *len);
char *sgets(char *s, const size_t size, char **p);

// Use this for getting a container type from a pointer to an element
#define container_of(ptr, type, member) ({ \
                const typeof( ((type *)0)->member ) *__mptr = (ptr); \
                (type *)( (char *)__mptr - offsetof(type,member) );})
#endif

