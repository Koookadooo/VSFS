#include "inode.h"
#include "block.h"
#include "free.h"
#include <stddef.h>
#include <stdio.h>

int ialloc(void) {
    unsigned char block[4096];

    if (bread(0, block) == NULL) {
        printf("Error reading block\n");
        return -1;
    }
    int inode = find_free(block);
    if (inode == -1) {
        printf("No free inodes\n");
        return -1;
    }
    set_free(block, inode, 1);
    bwrite(0, block);
  
    return inode;
}
