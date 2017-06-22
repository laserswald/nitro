#include <stdlib.h>
#include <xcb/xcb.h>
#include "globals.h"
#include "client.h"

struct ni_client {
    xcb_window_t window;
};

struct ni_client* ni_client_new(xcb_window_t window){
    struct ni_client* ret = malloc(sizeof ret);
    ret->window = window;

    // Listen to events
	uint32_t values[2];
	values[0] = XCB_EVENT_MASK_ENTER_WINDOW;
	values[1] = XCB_EVENT_MASK_FOCUS_CHANGE;
	xcb_change_window_attributes(conn, ret->window, XCB_CW_EVENT_MASK, values);

    return ret;
}

int ni_client_init(struct ni_client* this){
}

void ni_client_free(struct ni_client* this){
    free(this);
}

void ni_client_focus(struct ni_client* this){
	xcb_set_input_focus(conn, XCB_INPUT_FOCUS_POINTER_ROOT, this->window, XCB_CURRENT_TIME);

	xcb_flush(conn);
}

void ni_client_raise(struct ni_client* this){
}

void ni_client_lower(struct ni_client* this){
}

void ni_client_close(struct ni_client* this){
    xcb_kill_client(conn, this->window);
}

void ni_client_teleport(struct ni_client* this){
}

void ni_client_resize(struct ni_client* this){
}

void ni_client_border(struct ni_client* this){
}

void ni_client_undo_resize(struct ni_client* this){
}

// Comparison function for ni_clients.
int ni_client_cmp(void *a, void *b){
    ni_client_t *ac = a;
    ni_client_t *bc = b;
    // Yeah, yeah, "ordering" makes no sense. Whatever.
    return ac->window - bc->window;
}

