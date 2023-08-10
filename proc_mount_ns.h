#pragma once

struct mount_ns {
    struct inode* root_inode;
    struct mount_ns* parent_ns;
};
