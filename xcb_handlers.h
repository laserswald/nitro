#ifndef NI_XCB_HANDLERS

#define NI_XCB_HANDLERS

#include "event.h"


int xcb_create_no_handler(ni_event_t* event, dlist(ni_client)*);
int xcb_delete_no_handler(ni_event_t* event, dlist(ni_client)*);
int xcb_enter_no_handler(ni_event_t* event, dlist(ni_client)*);
int xcb_map_no_handler(ni_event_t* event, dlist(ni_client)*);
int xcb_circulate_rq_handler(ni_event_t* event, dlist(ni_client)*);
int xcb_client_msg_handler(ni_event_t* event, dlist(ni_client)*);
int xcb_config_no_handler(ni_event_t* event, dlist(ni_client)*);
int xcb_config_rq_handler(ni_event_t* event, dlist(ni_client)*);
int xcb_focus_out_handler(ni_event_t* event, dlist(ni_client)*);

#endif /* end of include guard: NI_XCB_HANDLERS */

