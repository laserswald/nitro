#ifndef NI_CLIENT

#define NI_CLIENT

#include <xcb/xcb.h>

#include "geometry.h"
#include "dlist.h"

// A client window.
typedef struct ni_client ni_client_t;
dlist_declare(ni_client_t*, ni_client);

// Allocate a new client
ni_client_t* ni_client_new(xcb_window_t window);

// Initialize a stack allocated client
int ni_client_init(ni_client_t*);

// Free a heap allocated client
void ni_client_free(ni_client_t*);

// Place focus on this client
void ni_client_focus(ni_client_t*);

// Raise this client to front
void ni_client_raise(ni_client_t*);

// Lower this client to back
void ni_client_lower(ni_client_t*);
void ni_client_close(ni_client_t*);
void ni_client_teleport(ni_client_t*);
void ni_client_resize(ni_client_t*);
void ni_client_border(ni_client_t*);
void ni_client_undo_resize(ni_client_t*);

#endif /* end of include guard: NI_CLIENT */
