#include <assert.h>
#include "ind.h"
#include "emit.h"

ni_emitter* ni_emitter_new(){
    ni_emitter* this = mallocz(sizeof(*this), 2);
}

void ni_emitter_free(ni_emitter* this){
    assert(this != NULL);
    free(this);
    this = NULL;
}

xcb_generic_event_t* ni_emitter_get_event(ni_emitter* this){
    xcb_get_event(); 
}


