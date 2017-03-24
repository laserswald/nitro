#ifndef NI_EVENT_H
#define NI_EVENT_H

#include <assert.h>
#include <string.h>
#include "client.h"
#include "ind.h"

/**
 * What kind of argument this is.
 */
enum ni_event_arg_type {
    NI_EVENT_ARG_STRING,
    NI_EVENT_ARG_NUMBER
};

/** Variant type for an event argument.
 */
typedef struct ni_event_arg {
    enum ni_event_arg_type type;
    union {
        int number;
        char* string;
    };
} ni_event_arg_t;
dlist_declare(ni_event_arg_t, ni_event_arg);

// Make an event arg given a variable.
#define ni_event_arg_new(T)              \
    _Generic((T),                        \
            int: ni_event_arg_num,       \
            char*: ni_event_arg_str)(T)

#define ni_event_arg_get(T, arg) \
    _Generic((T), \
            int*: ni_event_arg_get_num, \
            char**: ni_event_arg_get_str \
            )(T, arg)

// You don't have to use these at all. Use the above for generic goodness.
ni_event_arg_t* ni_event_arg_num(int number);
ni_event_arg_t* ni_event_arg_str(char* string);
void ni_event_arg_get_num(int* number, ni_event_arg_t* argument);
void ni_event_arg_get_str(char** string, ni_event_arg_t* argument);

typedef struct ni_event {
    char* event_name;
    dlist(ni_event_arg) *arguments;
    void *extra;
} ni_event_t;
dlist_declare(ni_event_t, ni_event);

ni_event_t *ni_event_new(const char* name, dlist(ni_event_arg)* arguments, void* data);
void ni_event_free(ni_event_t* event);
ni_event_t *ni_event_from_xcb(xcb_generic_event_t *event);

#endif /* end of include guard: NI_EVENT_H */
