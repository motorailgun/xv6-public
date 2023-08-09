#include "types.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "x86.h"
#include "spinlock.h"

#include "proc_pid_ns.h"

struct pid_ns root_pid_ns = {
    .ns_id = 0,
    .parent = (struct pid_ns*)0,
    .children = {0},
};

enum pid_ns_relation {
    EQUAL, PARENT, CHILD, DIVORCED,
};

int pid_ns_usage_table[NPROC];

void pidns_init(void) {
    memset(pid_ns_usage_table, 0, sizeof(pid_ns_usage_table));
}

int search_for_child(struct pid_ns* start, int ns_id) {
    if(__builtin_expect(start->children[0] == 0, 1)) {
        return -1;
    } else {
        struct pid_ns** pid_ns = start->children;
        for(int i = 0; *(pid_ns + i) != 0; i++) {
            if((*(pid_ns + i))->ns_id == ns_id) {
                return 1;
            } else {
                if(search_for_child(*(pid_ns + i), ns_id) == 1) {
                    return 1;
                }
            }
        }

        return -1;
    }
}

int search_for_parent(struct pid_ns* start, int ns_id) {
    if(__builtin_expect(start->parent == 0, 1)) {
        return -1;
    } else {    
        for(struct pid_ns* parent = start->parent;
            parent != 0;
            parent = parent->parent) {
                if(parent->ns_id == ns_id) {
                    return 1;        
                }
            }
        return -1;
    }
}

enum pid_ns_relation pid_ns_relation(struct pid_ns* base, struct pid_ns* relative) {
    if(base->ns_id == relative->ns_id) {
        return EQUAL;
    }
    if(search_for_child(base, relative->ns_id) == 1) {
        return CHILD;
    }
    if(search_for_parent(base, relative->ns_id) == 1) {
        return PARENT;
    }

    return DIVORCED;
}

struct pid_ns alloc_pid_ns(struct pid_ns* parent) {
    for(int i = 0; i < NPROC; i++) {
        if(!pid_ns_usage_table[i]) {
            struct pid_ns new_pid_ns = {
                .ns_id = i,
                .parent = parent,
                .children = {0},
            };

            return new_pid_ns;
        }
    }

    struct pid_ns invalid_pid_ns = {
        .ns_id = -1,
        .parent = 0,
        .children = {0},
    };

    return invalid_pid_ns;
}
