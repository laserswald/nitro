#ifndef BF_HANDLER

#define BF_HANDLER

#include "client.h"

/** Backflip event handler */
typedef int (*bf_handler_func)(struct bf_cli_list *, void *);

struct bf_handler {
    char *event_name;
    bf_handler_func handler_func;
};

struct bf_handler_list {
    struct bf_handler *handler;
    struct bf_handler_list *next;
};
struct bf_handler* bf_handler_new(const char *, bf_handler_func);

void bf_handler_add(struct bf_handler_list **, struct bf_handler *);

int bf_handler_handle(struct bf_handler_list *, const char *, struct bf_cli_list *, void *);

void bf_handler_list_free(struct bf_handler_list *);

#endif /* end of include guard: BF_HANDLER */
