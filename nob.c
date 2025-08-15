#define PATH_MAX 4096
#define NOB_IMPLEMENTATION
#include "nob.h"
#define DEBUG "-g","-Wno-unused-parameter","-Wno-unknown-pragmas","-Wno-missing-braces"
#define OPFLUG "-s","-O3","-Os"
#define LINK "-Wl,--gc-sections","-lraylib","-lGL","-lm","-lpthread","-ldl","-lrt","-lX11"
#define LIB  "-I","./raylib-5.5_linux_amd64/include","-L","./raylib-5.5_linux_amd64/lib"
#define BUILD_FOLDER "./build/"

int main(int argc, char **argv)
{
    bool build_success = true;
    NOB_GO_REBUILD_URSELF(argc, argv);
    Nob_Cmd cmd = {0};
    if (!nob_mkdir_if_not_exists(BUILD_FOLDER)) return 1;

    nob_cmd_append(&cmd, "gcc", "-Wall", "-Wextra", DEBUG, "genmap.c", "-o", BUILD_FOLDER"genmap");
    if (!nob_cmd_run_sync_and_reset(&cmd)) build_success = false;
    nob_cmd_append(&cmd, "gcc", "-Wall", "-Wextra", DEBUG, "redmap.c", "-o", BUILD_FOLDER"redmap");
    if (!nob_cmd_run_sync_and_reset(&cmd)) build_success = false;
    nob_cmd_append(&cmd, "gcc", "-Wall", "-Wextra", DEBUG, "edit_raylib.c", "-o", BUILD_FOLDER"editor");
    nob_cmd_append(&cmd, LINK, LIB);
    if (!nob_cmd_run_sync_and_reset(&cmd)) build_success = false;
    if(build_success){
        /* nob_cmd_append(&cmd, "./build/genmap"); */
        /* if (!nob_cmd_run_sync_and_reset(&cmd)) return 1; */
        /* nob_cmd_append(&cmd, "./build/redmap", "./the4.btb"); */
        /* if (!nob_cmd_run_sync_and_reset(&cmd)) return 1; */
        nob_cmd_append(&cmd, BUILD_FOLDER"editor");
        if (!nob_cmd_run_sync_and_reset(&cmd)) return 1;
    }

    return 0;
}
