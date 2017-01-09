#ifndef NI_HANDLER

#define NI_HANDLER

#include "client.h"

/** Backflip event handler */
typedef int (*ni_handler_func)(struct ni_cli_list *, void *);

struct ni_handler {
    char *event_name;
    ni_handler_func handler_func;
};

struct ni_handler_list {
    struct ni_handler *handler;
    struct ni_handler_list *next;
};
struct ni_handler* ni_handler_new(const char *, ni_handler_func);

void ni_handler_add(struct ni_handler_list **, struct ni_handler *);

int ni_handler_handle(struct ni_handler_list *, const char *, struct ni_cli_list *, void *);

void ni_handler_list_free(struct ni_handler_list *);

#endif /* end of include guard: NI_HANDLER */
