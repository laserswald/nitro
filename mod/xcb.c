#include <stdio.h>

#include "../globals.h"
#include "../handle.h"

int dummy_handler(dlist(ni_client) *clients, void *data){
    puts("I'm a dummy handler.");
}

int ni_mod_load(){
    struct ni_handler *dummy = ni_handler_new("dummy", &dummy_handler);
    dlist_append(ni_handler, handlers, dummy);
}


