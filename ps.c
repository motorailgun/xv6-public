#include "types.h"
#include "stat.h"
#include "user.h"
#include "param.h"

int main(int argc, char *argv[]) {
    printf(1, "here1\n");
    struct proc* proclist_ptr = malloc(NPROC * sizeof(struct proc));
    proclist();
    
    printf(2, "here2\n");
  
    exit();
}
