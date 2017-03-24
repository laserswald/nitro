#ifndef NI_XCB_HANDLERS

#define NI_XCB_HANDLERS

#include "event.h"

int xcb_map_no_handler(ni_event_t* event, dlist(ni_client)*);
int xcb_create_no_handler(ni_event_t* event, dlist(ni_client)*);
int xcb_delete_no_handler(ni_event_t* event, dlist(ni_client)*);
int xcb_enter_no_handler(ni_event_t* event, dlist(ni_client)*);

void xcb_config_rq_handler(xcb_generic_event_t *);
void xcb_config_no_handler(xcb_generic_event_t *);
void xcb_enter_no_handler(xcb_generic_event_t *);
void xcb_client_msg_handler(xcb_generic_event_t *);
void xcb_circulate_rq_handler(xcb_generic_event_t *);
void xcb_focus_out_handler(xcb_generic_event_t *);

#endif /* end of include guard: NI_XCB_HANDLERS */

