#ifndef BF_GEOMETRY

#define BF_GEOMETRY

#include <stdbool.h>

/* Rectangular geometry for manipulating windows. */

typedef struct rectangle {
    int x, y;
    unsigned int w, h;
} rect_t;

/* Initialize (or allocate a new) rectangle. */
int rect_init(rect_t*, int, int, unsigned int, unsigned int);

/* Return true if the second rectangle is contained entirely within the first. */
bool rect_within(const rect_t*, const rect_t*);

/* Return true when two rectangles collide (either touch or overlap) */
bool rect_collide(const rect_t*, const rect_t*);

/* Free a dynamically allocated rectangle. */
void rect_free(rect_t*);

#endif /* end of include guard: BF_GEOMETRY */
