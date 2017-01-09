#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "handle.h"

struct bf_handler* bf_handler_new(const char *name, bf_handler_func function){
    struct bf_handler* h = malloc(sizeof(struct bf_handler));
    h->event_name = strdup(name);
    h->handler_func = function;
    return h;
}

/*
 * Add a handler to the given handler list. Returns a new handler list if none was given.
 */

void bf_handler_add(struct bf_handler_list **list, struct bf_handler *handler){
    // no handler, no problem. Don't do anything.
    if (!handler) 
        return;

    // we need a handler list item for this handler
    struct bf_handler_list *link = calloc(1, sizeof(struct bf_handler_list)); 

    link->handler = handler;

    // if we weren't given a list at first, this is now the whole list
    if (!(*list)) {
        *list = link;
        return;
    }

    // Find the last item
    struct bf_handler_list *cursor;
    for (cursor = *list; cursor->next == NULL; cursor = cursor->next)
        ;
    cursor->next = link;
}

/*
 * Using the given handler list, call the correct handler.
 */

int bf_handler_handle(struct bf_handler_list *list, const char *name, struct bf_cli_list *clients, void *data){

    if (!list) return -1;
    if (!name) return -1;
    
    struct bf_handler_list *cursor = list;
    while (cursor != NULL) {
        assert(cursor);
        if (strcmp(cursor->handler->event_name, name) == 0) break;
        cursor = cursor->next;
    }

    // cursor is either NULL or the handler we want now 
    if (cursor == NULL){
        fprintf(stderr, "Could not find handler %s. Check the plugins.", name);
        return -1;
    }

    // And now we have the correct handler. Let's call it!
    return cursor->handler->handler_func(clients, data);
}

void bf_handler_list_free(struct bf_handler_list *list){
    struct bf_handler_list *cursor = list;
    while (cursor != NULL){
        struct bf_handler_list *previous = cursor;
        cursor = cursor->next;
        free(previous);
    }
    // Just making sure this pointer is now nothing
    list = NULL;
}

