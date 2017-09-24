#include <assert.h>
#include <string.h>
#include <xcb/xcb.h>
#include "ind.h"
#include "globals.h"
#include "emit.h"

void* ni_dummy_get_event(ni_emitter *this);
void ni_dummy_free(ni_emitter *this);

ni_emitter* ni_emitter_new(){
    ni_emitter* this = mallocz(sizeof(*this), 2);
    this->get_event = &ni_dummy_get_event;
    this->destroy = &ni_dummy_free;
    return this;
}

void ni_emitter_free(ni_emitter* this){
    assert(this != NULL);
    this->destroy(this);
    this = NULL;
}

void* ni_emitter_get_event(ni_emitter* this){
    return this->get_event(this);
}

// Basic emitter implementations

void* ni_dummy_get_event(ni_emitter *this){
    char* event= "exit";
    return memdupz(event, strlen(event));
}

void ni_dummy_free(ni_emitter *this){
    return;
}

