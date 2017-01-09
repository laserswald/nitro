#include <stdlib.h>
#include <stdio.h>

#include "handle.h"
#include "modules.h"
        
struct bf_handler_list *handlers = NULL;

void initialize() {
}

void shutdown(){
    bf_handler_list_free(handlers);
}

int main(int argc, const char *argv[])
{
    initialize();
    bf_load_mods("./modbins"); 
    bf_handler_handle(handlers, "dummy", NULL, NULL);
    return 0;
}

