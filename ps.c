#include "proc_mount_ns.h"
#include "proc_pid_ns.h"
#include "types.h"
#include "stat.h"
#include "user.h"
#include "param.h"
#include "x86.h"

__attribute__((packed)) struct context {
  uint edi;
  uint esi;
  uint ebx;
  uint ebp;
  uint eip;
};

enum procstate { UNUSED, EMBRYO, SLEEPING, RUNNABLE, RUNNING, ZOMBIE };

// Per-process state
__attribute__((packed)) struct proc {
  uint sz;                     // Size of process memory (bytes)
  pde_t* pgdir;                // Page table
  char *kstack;                // Bottom of kernel stack for this process
  enum procstate state;        // Process state
  int pid;                     // Process ID
  struct proc *parent;         // Parent process
  struct trapframe *tf;        // Trap frame for current syscall
  struct context *context;     // swtch() here to run process
  void *chan;                  // If non-zero, sleeping on chan
  int killed;                  // If non-zero, have been killed
  struct file *ofile[NOFILE];  // Open files
  struct inode *cwd;           // Current directory
  char name[16];               // Process name (debugging)

  struct pid_ns pid_namespace;     // Process namspace
  struct mount_ns mount_namespace; // chroot root inode
};

int main(int argc, char *argv[]) {
  printf(1, "here1\n");
  
  struct proc* proclist_ptr = malloc(NPROC * sizeof(struct proc));
  int count = proclist(proclist_ptr);
  
  printf(2, "offset of mount_ns = %d\n", (void*)&proclist_ptr->mount_namespace - (void*)proclist_ptr);
  for(int i = 0; i < count; i++) {
    struct proc* cur_ptr = proclist_ptr + i;
    printf(2, "pid: %d, name: %s, pid namespace: %d, inode*: %d\n", 
      cur_ptr->pid,
      cur_ptr->name,
      cur_ptr->pid_namespace,
      ((int*)(((void*)cur_ptr) + 388))
    );

    for(int j = 0; j < sizeof(struct proc); j++){
      printf(2, "%x", *((unsigned char*)cur_ptr + j));
      if(j % 80 == 0) {
        printf(2, "\n");
      }
    }
    printf(2, "\n\n");
  }
  
  printf(2, "here2\n");

  exit();
}
