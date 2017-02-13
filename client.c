#include <stdlib.h>
#include <xcb/xcb.h>
#include "globals.h"
#include "client.h"

ni_client* ni_client_new(){
    ni_client* ret = malloc(sizeof ret);
    return ret;
}

int ni_client_init(ni_client* this){
}

void ni_client_free(ni_client* this){
    free(this->window);
    free(this);
}

void ni_client_focus(ni_client* this){
	xcb_set_input_focus(conn, XCB_INPUT_FOCUS_POINTER_ROOT, this->window, XCB_CURRENT_TIME);

	xcb_flush(conn);
}

void ni_client_raise(ni_client* this){
}

void ni_client_lower(ni_client* this){
}

void ni_client_close(ni_client* this){
}

void ni_client_teleport(ni_client* this){
}

void ni_client_resize(ni_client* this){
}

void ni_client_border(ni_client* this){
}

void ni_client_undo_resize(ni_client* this){
}

