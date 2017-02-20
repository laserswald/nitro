#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "handle.h"

struct ni_handler* ni_handler_new(const char *name, ni_handler_func function){
    struct ni_handler* h = malloc(sizeof(struct ni_handler));
    h->event_name = strdup(name);
    h->handler_func = function;
    return h;
}

/*
 * Using the given handler list, call the correct handler.
 */

int ni_handler_handle(dlist(ni_handler) *list, const char *name, dlist(ni_client) *clients, void *data){

    if (!list) return -1;
    if (!name) return -1;

    bool found_handler = false;

    dlist(ni_handler) *cursor = NULL;
    dlist_foreach(list, cursor){
        printf("Comparing '%s' with '%s' \n", cursor->data->event_name, name);
        if (strcmp(cursor->data->event_name, name) == 0) {
            cursor->data->handler_func(clients, data);
            found_handler = true;
        }
    }
    // cursor is either NULL or the handler we want now
    if (found_handler == false){
        fprintf(stderr, "nitro - could not find handler %s. \n", name);
        return -1;
    }
}


