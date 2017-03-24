
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

char* stringify_xcb_event_name(xcb_generic_event_t *event){
    char* names[XCB_GET_MODIFIER_MAPPING+1];
    for (int i = 0; i < XCB_GET_MODIFIER_MAPPING + 1; i++){
        names[i] = NULL;
    }

	names[XCB_CONFIGURE_REQUEST] = "xcb_configure_request";
	names[XCB_DESTROY_NOTIFY]    = "xcb_destroy_notify";
	names[XCB_CREATE_NOTIFY]     = "xcb_create_notify";
	names[XCB_ENTER_NOTIFY]      = "xcb_enter_notify";
	names[XCB_MAP_REQUEST]       = "xcb_map_request";
	names[XCB_MAP_NOTIFY]        = "xcb_map_notify";
	names[XCB_UNMAP_NOTIFY]      = "xcb_unmap_notify";
	names[XCB_CLIENT_MESSAGE]    = "xcb_client_message";
	names[XCB_CONFIGURE_NOTIFY]  = "xcb_configure_notify";
	names[XCB_CIRCULATE_REQUEST] = "xcb_circulate_request";
	names[XCB_FOCUS_OUT]         = "xcb_focus_out";
    char* string = names[event->response_type & ~0x80];

    if (string == NULL)
        return NULL;

    puts(string);
    return memdupz(string, strlen(string));
}

struct ni_event *ni_event_from_xcb(xcb_generic_event_t *event){
    if (!event)
        return NULL;

    char* event_name = stringify_xcb_event_name(event);
    if (!event_name)
        return NULL;

    return ni_event_new(event_name, NULL, event);
}

void ni_event_free(ni_event_t *event){

}

