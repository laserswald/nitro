#ifndef NI_EMITTERS

#define NI_EMITTERS

#include <xcb/xcb.h>

#include "dlist.h"

// Just... something
typedef struct _ni_emitter {
    void* (*get_event)(struct _ni_emitter*);
    void (*destroy)(struct _ni_emitter*);
} ni_emitter;

dlist_declare(ni_emitter*, ni_emitter);

ni_emitter* ni_emitter_new();
int ni_emitter_init(ni_emitter* this);
void ni_emitter_free(ni_emitter* this);
void* ni_emitter_get_event(ni_emitter* this);


#endif /* end of include guard: NI_EMITTERS */
