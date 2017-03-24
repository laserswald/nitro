#ifndef NI_GLOBALS

#define NI_GLOBALS

#include "client.h"
#include "emit.h"
#include "handle.h"

extern dlist(ni_client)  *all_clients;
extern dlist(ni_handler) *handlers;
extern dlist(ni_emitter) *emitters;
extern xcb_connection_t *conn;
extern bool is_running;


#endif /* end of include guard: NI_GLOBALS */
