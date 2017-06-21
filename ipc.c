#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

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


/**
 * Convert a string to a ni_event.
 */
static
ni_event *ni_ipc_strtoevent(char *string, int len){

}

void* ni_ipc_get_event(ni_emitter *emitter){
    // upcast. Pretty dangerous, but who cares.
    struct ni_ipc* this = (struct ni_ipc*) emitter;

    if (!this->buffer) {
        int amount = 0;
        this->buffer = readtoeoffd(this->infd, &amount);
        if (amount == 0) {
            this->buffer = NULL;
            // We don't have any events here.
            return NULL;
        }
    }
    char *nl = strchr(this->buffer, '\n');
    char *line = malloc(nl - this->buffer + 1);
    sgets(line, nl - data + 1, data);

    ni_event *evt = ni_ipc_strtoevent(line, nl-data);

    free(line);
    return evt;
}

struct ni_ipc* ni_ipc_new(const char* fin, const char* fout){
    struct ni_ipc *this = mallocz(sizeof(*this), 2);
    this->emitter.get_event = &ni_ipc_get_event;
    // Make the file nodes
    mkfifo(fin, O_RDONLY);

    // Start listening
    this->infd = open(fin, O_RDONLY | O_NDELAY);

    return this;
}
