#include "types.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "x86.h"
#include "proc.h"
#include "spinlock.h"

struct mount_ns root_mount_ns = {
    .root_inode = (struct inode*)0,
    .parent_ns = (struct mount_ns*)0,
};

void mountns_init(void) {
    root_mount_ns.root_inode = namei("/");
    cprintf("namei: %d\n", namei("/"));
}

struct mount_ns gen_mount_ns(char* path) {
    struct inode* path_inode = namei(path);
    struct mount_ns new_mount_ns;

    if(path_inode == 0) {
        new_mount_ns.root_inode = (struct inode*) -1;
        return new_mount_ns;
    }

    new_mount_ns.root_inode = path_inode;
    new_mount_ns.parent_ns = &myproc()->mount_namespace;

    return new_mount_ns;
}
