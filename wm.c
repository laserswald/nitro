#include <stdlib.h>
#include <stdio.h>

#include "dlist.h"
#include "ind.h"
#include "globals.h"
#include "handle.h"
#include "modules.h"
#include "xcb_handlers.h"
        
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
    dlist_free(handlers, ni_handler);
}

void add_default_handlers(){
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

void listen(){
    while (is_running) {
        dlist(ni_emitter) *current;
        dlist_foreach(current, emitters){
            xcb_generic_event_t *event = ni_emitter_get_event(current->data);
            if (event){
                // Get the name of the event
                char* name = "";
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

    // Start any plugin startup functions.
    ni_handler_handle(handlers, "start", NULL, NULL);

    // Start listening for events.
    listen();

    return 0;
}

