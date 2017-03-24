#ifndef NI_IPC_H

#define NI_IPC_H

#include "emit.h"

typedef struct ni_ipc ni_ipc_t;

ni_ipc_t* ni_ipc_new(const char* fin, const char* fout);

#endif /* end of include guard: NI_IPC_H */
