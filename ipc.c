#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "deps/dlist/dlist.h"
#include "emit.h"
#include "event.h"
#include "ind.h"
#include "ipc.h"

struct ni_ipc {
    ni_emitter emitter;
    int infd;
    int outfd;
    char *buffer; // Storage for later event processing
};

struct ni_ipc* ni_ipc_new(const char* fin, const char* fout){
    struct ni_ipc *this = mallocz(sizeof(*this), 2);
    this->emitter.get_event = &ni_ipc_get_event;
    this->emitter.destroy = &ni_ipc_free;
    // Make the file nodes
    mkfifo(fin, S_IRWXU | S_IRWXG);

    // Start listening
    this->infd = open(fin, O_RDONLY | O_NONBLOCK);

    return this;
}

void ni_ipc_free(struct ni_ipc *ipc){
    if (ipc) {
        close(ipc->infd);
    }
    free(ipc);
}

/**
 * Convert a string to a ni_event.
 */
static
ni_event_t *ni_ipc_strtoevent(char *string){
    ni_event_t *retval = NULL;
    if (string) {
        char* evt_name = strsep(&string, "\t ");
        dlist(ni_event_arg) *args = NULL;
        while (string){
            char *argstr = strsep(&string, "\t ");
            char *end;
            int possible_num = strtol(argstr, &end, 10);
            if (end == '\0') {
                dlist_push(ni_event_arg, args, *ni_event_arg_num(possible_num));
            }
        }
        retval = ni_event_new(evt_name, args, NULL);
    }
    return retval;
}

char* ni_ipc_get_line(ni_emitter *emitter){
    struct ni_ipc* ipc = (struct ni_ipc*) emitter;

    int amount = 0;
    if (!ipc->buffer) {
        ipc->buffer = readtoeoffd(ipc->infd, &amount);
        if (0 == amount) {
            return NULL;
        }
    }

    char *line = malloc(255);
    sgets(line, 255, &ipc->buffer);

    return line;
}

ni_event_t *ni_ipc_get_event(ni_emitter *emitter){
    ni_event_t *retval = NULL;

    char *line = ni_ipc_get_line(emitter);
    if (line) {
        retval = ni_ipc_strtoevent(line);
    }

    return retval;
}

