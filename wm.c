#include <stdlib.h>
#include <stdio.h>

#include "dlist.h"
#include "ind.h"
#include "globals.h"
#include "handle.h"
#include "modules.h"
#include "xcb_handlers.h"

// Initialize global variables.
dlist(ni_handler) *handlers = NULL;
dlist(ni_emitter) *emitters = NULL;
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
    ni_handler_handle(handlers, "end", NULL, NULL);
    dlist_free(ni_handler, handlers);
    dlist_free(ni_emitter, emitters);
}

int handle_exit(dlist(ni_client)* clients, void* data){
    is_running = false;
}

void add_default_handlers(){
    ni_handler* exit_handler = ni_handler_new("exit", handle_exit);
    dlist_append(ni_handler, handlers, exit_handler);
    /* ni_handler_new("xcb_configure_request", xcb_config_rq_handler); */
    /* ni_handler_new("xcb_configure_notify", xcb_config_no_handler); */
    /* ni_handler_new("xcb_destroy_notify", xcb_destroy_no_handler); */
    /* ni_handler_new("xcb_enter_notify", xcb_enter_no_handler); */
    /* ni_handler_new("xcb_map_request", xcb_map_rq_handler); */
    /* ni_handler_new("xcb_map_notify", xcb_map_no_handler); */
    /* ni_handler_new("xcb_client_message", xcb_client_msg_handler); */
    /* ni_handler_new("xcb_circulate_request", xcb_circulate_rq_handler); */
    /* ni_handler_new("xcb_focus_out", xcb_focus_out_handler); */
}

void add_default_emitters(){
    ni_emitter* xcb_emit = ni_emitter_new();
    dlist_append(ni_emitter, emitters, xcb_emit);
}

void listen(){
    while (is_running) {
        dlist(ni_emitter) *current = NULL;
        dlist_foreach(emitters, current){
            char *event = ni_emitter_get_event(current->data);
            if (event != NULL){
                // Get the name of the event
                char* name = event;
                // handle it
                ni_handler_handle(handlers, name, NULL, NULL);
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
    // ni_handler_handle(handlers, "start", NULL, NULL);

    // Start listening for events.
    listen();

    return 0;
}

