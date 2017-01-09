#include <stdlib.h>

#include "geometry.h"

int rect_init(rect_t *r, int x, int y, unsigned int w, unsigned int h){
    if (!r) r = malloc(sizeof(rect_t));
    r->x = x;
    r->y = y;
    r->w = w;
    r->h = h;
}

// returns true if A is within B
bool rect_within(const rect_t *a, const rect_t *b){
    if (a->x >= b->x && 
        a->y >= b->y && 
        a->x + a->w <= b->x + b->w &&
        a->y + a->h <= b->y + b->h)
        return true;
    else return false;
}

// returns true if A and B touch
bool rect_collide(const rect_t *a, const rect_t *b){
    if (rect_within(a, b)) return true;
    if (a->x > b->x + b->w ||
        a->y > b->y + b->h ||
        b->x > a->x + a->w ||
        b->y > a->y + a->h) return false;
    return true;
}

