#define NOB_IMPLEMENTATION
#include <nob.h>

int main(int argc, char **argv) {
    NOB_GO_REBUILD_URSELF(argc,argv);
    Nob_Cmd cmd = {0};
    nob_cmd_append(&cmd,"cc");
    nob_cmd_append(&cmd,"-Wall","-Wextra","-ggdb");
    nob_cmd_append(&cmd,"-o","build/main");
    nob_cmd_append(&cmd,"main.c");
    nob_cmd_append(&cmd,"-lraylib", "-lm");
    if(!nob_cmd_run_sync(cmd)) return 1;
    return 0;
}
