#ifndef NI_CLIENT

#define NI_CLIENT

#include <xcb/xcb.h>

#include "geometry.h"
#include "dlist.h"

typedef struct ni_client {
    xcb_window_t *window;
} ni_client;

dlist_declare(ni_client*, ni_client);

ni_client* ni_client_new();
int ni_client_init(ni_client* this);
void ni_client_free(ni_client* this);

void ni_client_focus(ni_client* this);
void ni_client_raise(ni_client* this);
void ni_client_lower(ni_client* this);
void ni_client_close(ni_client* this);
void ni_client_teleport(ni_client* this);
void ni_client_resize(ni_client* this);
void ni_client_border(ni_client* this);
void ni_client_undo_resize(ni_client* this);

#endif /* end of include guard: NI_CLIENT */
