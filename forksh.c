#include "types.h"
#include "user.h"
#include "fcntl.h"

void usage(void) {
    printf(2, "usage: foksh namespace\n");
}

void panic(char *s)
{
  printf(2, "%s\n", s);
  exit();
}

int forkn(void) {
  int pid;

  pid = forkpidns();
  if(pid == -1)
    panic("fork2");
  return pid;
}

int main(int argc, char* argv[]) {
    int pid_namespace = atoi(argv[1]);
    if(pid_namespace < 0 ){
        printf(2, "given namespace invalid\n");
        usage();
        exit();
    }

    char* str = "sh";
    char* arg[] = {str, 0};

    if(forkn() == 0) {
        exec(str, arg);
        printf(2, "forkpidns on %d / sh failed\n", pid_namespace);
    }

    wait();
    exit();
}
