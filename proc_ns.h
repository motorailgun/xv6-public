#include "defs.h"
#define MAX_CHILD_PROC_NS (32)

struct proc_ns {
    struct inode *root_dir;
    int root_pid;
    char* name;
    struct proc_ns *children_ns;
};
