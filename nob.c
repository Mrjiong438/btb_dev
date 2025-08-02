#define PATH_MAX 4096
#define NOB_IMPLEMENTATION
#include "nob.h"
#define DEBUG "-Wno-unused-parameter"
#define OPFLUG "-s","-O3","-Os"
#define BUILD_FOLDER "./build/"

int main(int argc, char **argv)
{
    NOB_GO_REBUILD_URSELF(argc, argv);
    Nob_Cmd cmd = {0};
    if (!nob_mkdir_if_not_exists(BUILD_FOLDER)) return 1;

    nob_cmd_append(&cmd, "gcc", "-Wall", "-Wextra", DEBUG, "genmap.c", "-o", BUILD_FOLDER"genmap");
    if (!nob_cmd_run_sync_and_reset(&cmd)) return 1;
    nob_cmd_append(&cmd, "gcc", "-Wall", "-Wextra", DEBUG, "redmap.c", "-o", BUILD_FOLDER"redmap");
    if (!nob_cmd_run_sync_and_reset(&cmd)) return 1;
    /* nob_cmd_append(&cmd, "./build/genmap"); */
    /* if (!nob_cmd_run_sync_and_reset(&cmd)) return 1; */
    /* nob_cmd_append(&cmd, "./build/redmap", "./the4.btb"); */
    /* if (!nob_cmd_run_sync_and_reset(&cmd)) return 1; */

    return 0;
}
