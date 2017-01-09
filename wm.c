#include <stdlib.h>
#include <stdio.h>

#include "handle.h"
#include "modules.h"
        
struct ni_handler_list *handlers = NULL;

void initialize() {
}

void shutdown(){
    ni_handler_handle(handlers, "end", NULL, NULL);
    ni_handler_list_free(handlers);
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

    // Start any event emitters.
    start_default_emitters();

    // Start listening for events.

    return 0;
}

