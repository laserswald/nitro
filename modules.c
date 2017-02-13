#include <dirent.h>
#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

#include "ind.h"
#include "modules.h"

int _ni_load_module(const char *filename){
    void *dlhandle;
    int (*mod_entry)(void);
    dlhandle = dlopen(filename, RTLD_LAZY | RTLD_GLOBAL);
    if (!dlhandle){
        perror(dlerror());
    }
    mod_entry = dlsym(dlhandle, "ni_mod_load");
    if (!mod_entry) edie("nitro - could not load module '%s'", filename);
    return mod_entry();
}

int ni_load_mods(const char *directory){
    struct dirent *dirent;
    DIR *dir = opendir(directory);
    if (dir) {
        while (dirent = readdir(dir)) {
            if (dirent->d_type == DT_REG){
                char *fullpath = smprintf("%s/%s", directory, dirent->d_name);
                _ni_load_module(fullpath);
                free(fullpath);
            }
        }
        closedir(dir);
    }
}


