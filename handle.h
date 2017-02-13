#ifndef NI_HANDLER

#define NI_HANDLER

#include "client.h"
#include "dlist.h"

/** Backflip event handler */
typedef int (*ni_handler_func)(dlist(ni_client)*, void *);

struct ni_handler {
    char *event_name;
    ni_handler_func handler_func;
};

dlist_declare(struct ni_handler *, ni_handler);

struct ni_handler* ni_handler_new(const char *, ni_handler_func);

int ni_handler_handle( dlist(ni_handler) *, const char *, dlist(ni_client) *, void *);

#endif /* end of include guard: NI_HANDLER */
