#include "types.h"
#include "stat.h"
#include "user.h"

int
main(int argc, char **argv)
{
  int i;

  if(argc < 2){
    printf(2, "usage: kill pid...\n");
    exit();
  }

  for(i=1; i<argc; i++) {
    int pid;

    if(kill(pid = atoi(argv[i])) < 0) {
      printf(2, "failed to kill pid %d\n", pid);
    }
  }
  exit();
}
