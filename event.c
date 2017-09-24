
#include "event.h"

struct ni_event_arg* ni_event_arg_num(int number){
    struct ni_event_arg* argument = mallocz(sizeof (*argument), 2);
    argument->type = NI_EVENT_ARG_NUMBER;
    argument->number = number;
    return argument;
}

struct ni_event_arg* ni_event_arg_str(char* string){
    struct ni_event_arg* argument = mallocz(sizeof (*argument), 2);
    argument->type = NI_EVENT_ARG_STRING;
    argument->string = memdupz(string, strlen(string));
    return argument;
}

void ni_event_arg_get_num(int* number, struct ni_event_arg* this){
    assert(this != NULL);
    if (this->type != NI_EVENT_ARG_NUMBER){
        fprintf(stderr, "nitro: event argument is not a number, but treated like one.");
        exit(1);
    }
    *number = this->number;
}

void ni_event_arg_get_str(char** string, struct ni_event_arg* this){
    assert(this != NULL);
    if (this->type != NI_EVENT_ARG_STRING){
        fprintf(stderr, "nitro: event argument is not a string, but treated like one.");
        exit(1);
    }
    *string = this->string;
}

// ni_event implementation
struct ni_event *ni_event_new(const char* name, dlist(ni_event_arg)* arguments, void* data){
    if (!name)
        return NULL;
    struct ni_event *this = mallocz(sizeof (*this), 2);
    this->event_name = memdupz(name, strlen(name));
    this->arguments = arguments;
    this->extra = data;
    return this;
}

void ni_event_free(ni_event_t *event){

}

