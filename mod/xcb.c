#include <stdio.h>

#include "../globals.h"
#include "../client.h"
#include "../event.h"
#include "../handle.h"

int dummy_handler(ni_event_t* event, dlist(ni_client) *clients){
    puts("I'm a dummy handler.");
}

int ni_mod_load(){
    ni_handler_t *dummy = ni_handler_new("dummy", &dummy_handler);
    dlist_append(ni_handler, handlers, dummy);
}


