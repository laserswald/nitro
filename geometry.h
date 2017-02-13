#ifndef NI_GEOMETRY

#define NI_GEOMETRY

#include <stdbool.h>

/* Rectangular geometry for manipulating windows. */

typedef struct ni_rect{
    int x, y;
    unsigned int w, h;
} ni_rect;

/* Initialize (or allocate a new) rectangle. */
int ni_rect_init(ni_rect*, int, int, unsigned int, unsigned int);

/* Return true if the second rectangle is contained entirely within the first. */
bool ni_rect_within(const ni_rect*, const ni_rect*);

/* Return true when two rectangles collide (either touch or overlap) */
bool ni_rect_collide(const ni_rect*, const ni_rect*);

/* Free a dynamically allocated rectangle. */
void ni_rect_free(ni_rect*);

#endif /* end of include guard: NI_GEOMETRY */
