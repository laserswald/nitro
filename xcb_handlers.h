#ifndef NI_XCB_HANDLERS

#define NI_XCB_HANDLERS

void xcb_config_rq_handler(xcb_generic_event_t *);
void xcb_config_no_handler(xcb_generic_event_t *);
void xcb_destroy_no_handler(xcb_generic_event_t *);
void xcb_enter_no_handler(xcb_generic_event_t *);
void xcb_map_rq_handler(xcb_generic_event_t *);
void xcb_map_no_handler(xcb_generic_event_t *);
void xcb_client_msg_handler(xcb_generic_event_t *);
void xcb_circulate_rq_handler(xcb_generic_event_t *);
void xcb_focus_out_handler(xcb_generic_event_t *);

#endif /* end of include guard: NI_XCB_HANDLERS */

