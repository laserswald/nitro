#include "greatest.h"

SUITE_EXTERN(event_arg_suite);
SUITE_EXTERN(ipc_suite);

GREATEST_MAIN_DEFS();

int main(int argc, char **argv) {
    GREATEST_MAIN_BEGIN();
    RUN_SUITE(event_arg_suite);
    RUN_SUITE(ipc_suite);
    GREATEST_MAIN_END();
}
