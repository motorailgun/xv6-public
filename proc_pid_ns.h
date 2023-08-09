#pragma once

struct pid_ns {
    int ns_id;
    struct pid_ns* parent;
    struct pid_ns* children[64];
};
