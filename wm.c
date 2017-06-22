#include <stdlib.h>
#include <stdio.h>

#include "dlist.h"
#include "ind.h"
#include "globals.h"
#include "handle.h"
#include "modules.h"
#include "xcb_handlers.h"
#include "event.h"

// Initialize global variables.
dlist(ni_handler) *handlers = NULL;
dlist(ni_emitter) *emitters = NULL;
dlist(ni_client) *all_clients = NULL;
xcb_connection_t *conn = NULL;
bool is_running = false;

void initialize() {
    int screen;
    conn = xcb_connect(NULL, &screen);
    if (xcb_connection_has_error(conn)) {
        die("nitro: unable to connect to xcb.");
    }
    is_running = true;
}

void shutdown(){
    ni_event_t* exit_event = ni_event_new("exit", NULL, NULL);
    ni_handler_handle(handlers, exit_event, all_clients);
    dlist_free(ni_handler, handlers);
    dlist_free(ni_emitter, emitters);
}

int handle_exit(ni_event_t* event, dlist(ni_client)* clients){
    is_running = false;
    return 0;
}

void add_default_handlers(){
    ni_handler_t* exit_handler = ni_handler_new("exit", &handle_exit);
    dlist_push(ni_handler, handlers, exit_handler);
    /* ni_handler_new("xcb_map_request", xcb_map_rq_handler); */
    ni_handler_t* map_handler = ni_handler_new("xcb_map_notify", xcb_map_no_handler);
    dlist_push(ni_handler, handlers, map_handler);
}

void add_default_emitters(){
    ni_emitter* xcb_emit = ni_emitter_new();
    dlist_push(ni_emitter, emitters, xcb_emit);
}

void listen(){
    while (is_running) {
        dlist_foreach(ni_emitter, emitters, current){
            ni_event_t *event = ni_emitter_get_event(current->data);
            if (event != NULL) {
                printf("Got a message: %s\n", event->event_name);
                ni_handler_handle(handlers, event, all_clients);
                ni_event_free(event);
            }
        }
    }
}

int main(int argc, const char *argv[])
{
    initialize();
    atexit(shutdown);
    ni_load_mods("./modbins");

    // Load any built in listeners
    add_default_handlers();
    add_default_emitters();

    // Start any plugin startup functions.
    ni_event_t* start_event = ni_event_new("start", NULL, NULL);
    ni_handler_handle(handlers, start_event, NULL);

    // Start listening for events.
    listen();

    return 0;
}

