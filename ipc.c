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
};

void* ni_ipc_get_event(ni_emitter *emitter){
    // upcast. Pretty dangerous, but who cares.
    struct ni_ipc* this = (struct ni_ipc*) emitter;

    // Read some data from the fifo


    char buf[256]; // this should be fine...
    char *abuf = ""; // actual string data
    int len = 0;
    while ((len = read(this->infd, buf, 255)) != 0){
        // append the \0
        buf[255] = '\0';
        abuf = smprintf("%s%s", abuf, buf);

        // We need to concatenate buffers if it's past what we have
    }

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
