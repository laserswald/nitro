#ifndef NI_IPC_H

#define NI_IPC_H

#include "emit.h"
#include "event.h"

typedef struct ni_ipc ni_ipc_t;

ni_ipc_t *ni_ipc_new(const char* fin, const char* fout);
ni_event_t *ni_ipc_get_event(ni_emitter *emitter);
char *ni_ipc_get_line(ni_emitter *emitter);
void ni_ipc_free(ni_ipc_t *ipc);

#endif /* end of include guard: NI_IPC_H */
