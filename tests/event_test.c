#include "greatest.h"
#include "../event.h"

SUITE(event_arg_suite);

TEST event_arg_type(void){
    ni_event_arg_t* tester = ni_event_arg_new(5);
    int test;
    ni_event_arg_get(&test, tester);
    ASSERT_EQ(5, test);

    tester = ni_event_arg_new("This is a string");
    char* test_str;
    ni_event_arg_get(&test_str, tester);
    ASSERT_STR_EQ("This is a string", test_str);
    PASS();
}

GREATEST_SUITE(event_arg_suite){
    RUN_TEST(event_arg_type);
}
