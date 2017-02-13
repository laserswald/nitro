#include <stdio.h>
#include <xcb/xcb.h>
#include "xcb_handlers.h"

void xcb_config_rq_handler(xcb_generic_event_t *evt){
    puts("test handler");
}

void xcb_config_no_handler(xcb_generic_event_t *evt){
    puts("test handler");
}

void xcb_destroy_no_handler(xcb_generic_event_t *evt){
    puts("test handler");
}

void xcb_enter_no_handler(xcb_generic_event_t *evt){
    puts("test handler");
}

void xcb_map_rq_handler(xcb_generic_event_t *evt){
    puts("test handler");
}

void xcb_map_no_handler(xcb_generic_event_t *evt){
    puts("test handler");
}

void xcb_client_msg_handler(xcb_generic_event_t *evt){
    puts("test handler");
}

void xcb_circulate_rq_handler(xcb_generic_event_t *evt){
    puts("test handler");
}

void xcb_focus_out_handler(xcb_generic_event_t *){
    puts("test handler");
}

