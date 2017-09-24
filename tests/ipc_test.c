#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include "greatest.h"
#include "../ipc.h"

SUITE(ipc_suite);

ni_ipc_t *get_test_ipc(){
    return ni_ipc_new("infifo", "outfifo");
}

void send_msg(char* msg){
    int fd = open("infifo", O_WRONLY | O_NONBLOCK);
    dprintf(fd, "%s\n", msg);
    close(fd);
}

// Can we create and delete an IPC?
TEST ipc_create(void){
    ni_ipc_t *ipc = get_test_ipc();
    ASSERT(ipc != NULL);
    ni_ipc_free(ipc);
    PASS();
}

TEST ipc_returns_null_with_no_msgs(void){
    ni_ipc_t *ipc = get_test_ipc();

    ni_event_t *evt = ni_ipc_get_event(ipc);
    ASSERT_FALSE(evt);

    ni_ipc_free(ipc);
    PASS();
}

TEST ipc_returns_not_null_with_msg(void){
    ni_ipc_t *ipc = get_test_ipc();

    // Send an event.
    send_msg("This is a message!");

    ni_event_t *evt = ni_ipc_get_event(ipc);
    ASSERT(evt);

    ni_ipc_free(ipc);
    PASS();
}

TEST ipc_returns_line_given(void){
    ni_ipc_t *ipc = get_test_ipc();

    // Send an event.
    send_msg("This is a message!");

    char* message = ni_ipc_get_line(ipc);
    ASSERT(strcmp("This is a message!", message) == 0);

    ni_ipc_free(ipc);
    PASS();
}

TEST ipc_returns_correct_event(void) {
    ni_ipc_t *ipc = get_test_ipc();

    // Send an event.
    send_msg("event_name arg1 2");

    ni_event_t *evt = ni_ipc_get_event(ipc);
    ASSERT_STR_EQ("event_name", evt->event_name);

    ni_ipc_free(ipc);
    PASS();
}

TEST ipc_returns_correct_event_args(void) {
    ni_ipc_t *ipc = get_test_ipc();

    // Send an event.
    send_msg("event_name arg1 2");

    ni_event_t *evt = ni_ipc_get_event(ipc);
    ASSERT_STR_EQ("event_name", evt->event_name);
    ASSERT_STR_EQ("event_name", evt->event_name);

    ni_ipc_free(ipc);
    PASS();
}

GREATEST_SUITE(ipc_suite){
    RUN_TEST(ipc_create);
    RUN_TEST(ipc_returns_null_with_no_msgs);
    RUN_TEST(ipc_returns_not_null_with_msg);
    RUN_TEST(ipc_returns_line_given);
    RUN_TEST(ipc_returns_correct_event);
    RUN_TEST(ipc_returns_correct_event_args);
}
