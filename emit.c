#include <assert.h>
#include <xcb/xcb.h>
#include "ind.h"
#include "globals.h"
#include "emit.h"

void* ni_xcb_get_event(ni_emitter *this){
    return xcb_wait_for_event(conn);
}

ni_emitter* ni_emitter_new(){
    ni_emitter* this = mallocz(sizeof(*this), 2);
    this->get_event = &ni_xcb_get_event; 
    return this;
}

void ni_emitter_free(ni_emitter* this){
    assert(this != NULL);
    free(this);
    this = NULL;
}

void* ni_emitter_get_event(ni_emitter* this){
    return this->get_event(this);
}


