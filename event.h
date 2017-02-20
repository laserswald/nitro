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
} ni_event_arg;

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
struct ni_event_arg* ni_event_arg_num(int number);
struct ni_event_arg* ni_event_arg_str(char* string);
void ni_event_arg_get_num(int* number, struct ni_event_arg* this);
void ni_event_arg_get_str(char** string, struct ni_event_arg* this);

typedef struct ni_event {
    char* event_name;
    dlist(ni_client) *selected;
} ni_event;

#endif /* end of include guard: NI_EVENT_H */
