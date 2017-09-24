#include <stdlib.h>
#include <stdio.h>

#include "dlist.h"
#include "ind.h"
#include "globals.h"
#include "handle.h"
#include "modules.h"
#include "event.h"
#include "ipc.h"

// Initialize global variables.
dlist(ni_handler) *handlers = NULL;
dlist(ni_emitter) *emitters = NULL;
dlist(ni_client) *all_clients = NULL;
bool is_running = false;

void initialize() {
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
}

void add_default_emitters(){
    ni_emitter* ipc_emitter = (ni_emitter*) ni_ipc_new("/tmp/nitro-in", "/tmp/nitro-out");
    dlist_push(ni_emitter, emitters, ipc_emitter);
}

void listen(){
    while (is_running) {
        puts("running");
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

void destroy_handlers() {
    dlist_foreach(ni_handler, handlers, current) {
        free(current->data);
    }
}

void destroy_emitters() {
    dlist_foreach(ni_emitter, emitters, current) {
        ni_emitter_free(current->data);
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

    puts("Exiting");
    destroy_handlers();
    destroy_emitters();

    return 0;
}

