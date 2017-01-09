#include <stdio.h>

#include "../globals.h"
#include "../handle.h"

int dummy_handler(struct bf_cli_list *clients, void *data){
    puts("I'm a dummy handler.");
}

int bf_mod_load(){
    struct bf_handler *dummy = bf_handler_new("dummy", &dummy_handler);
    bf_handler_add(&handlers, dummy);
}


