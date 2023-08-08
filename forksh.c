#include "types.h"
#include "user.h"
#include "fcntl.h"

void usage(void) {
    printf(2, "usage: foksh namespace\n");
}

int main(int argc, char* argv[]) {
    if(argc < 2) {
        printf(2, "no enough arguments\n");
        usage();
        exit();
    }

    int pid_namespace = atoi(argv[1]);
    if(pid_namespace < 0 ){
        printf(2, "given namespace invalid\n");
        usage();
        exit();
    }

    char* str = "sh";
    char* arg[] = {str, 0};
    execpidns(pid_namespace, str, arg);
    printf(2, "execpidns on %d / sh failed\n", pid_namespace);
    exit();
}
