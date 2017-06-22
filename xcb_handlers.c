#include <stdio.h>
#include <xcb/xcb.h>

#include "ind.h"
#include "globals.h"
#include "dlist.h"
#include "xcb_handlers.h"

int xcb_map_no_handler(ni_event_t* event, dlist(ni_client)* selected){
    puts("test handler");
    return 0;
}

int xcb_create_no_handler(ni_event_t* event, dlist(ni_client)* selected){
    xcb_create_notify_event_t *evt;
    evt = event->extra;

    // Create a new client
    ni_client_t *cli = ni_client_new(evt->window);

    // Add it to the global list of windows
    dlist_append(ni_client, all_clients, cli);
    ni_client_focus(cli);
    exit(0);

    return 0;
}

int xcb_delete_no_handler(ni_event_t* event, dlist(ni_client)* selected){
    xcb_destroy_notify_event_t *evt;
    evt = event->extra;

    dlist(ni_client)* c = NULL;
    dlist_foreach(all_clients, c){

        ni_client_t *current = c->data;
        if (ni_client_cmp(current, evt->window)) {

            ni_client_close(current);
            ni_client_free(current);
        }
    }
    return 0;
}




