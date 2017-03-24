#ifndef NI_HANDLER

#define NI_HANDLER

#include "client.h"
#include "event.h"
#include "dlist.h"

/** Backflip event handler */
typedef int (*ni_handler_func)(ni_event_t* event, dlist(ni_client)*);

typedef struct ni_handler {
    char *event_name;
    ni_handler_func handler_func;
} ni_handler_t;

dlist_declare(ni_handler_t*, ni_handler);

struct ni_handler* ni_handler_new(const char *, ni_handler_func);

int ni_handler_handle (dlist(ni_handler)*, ni_event_t*, dlist(ni_client)*);

#endif /* end of include guard: NI_HANDLER */
