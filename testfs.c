#define CTEST_ENABLE
#include "image.h"
#include "block.h"
#include "ctest.h"
#include "free.h"
#include "inode.h"
#include <stdlib.h>

int main() {
    // Initialize testing variables and configure testing environment
    CTEST_VERBOSE(1);
    CTEST_COLOR(1);

    // Open the image file first and test opening
    CTEST_ASSERT(image_open("test.img", 1) != -1, "Open image file with truncation");

    // Initialize inode and block maps after truncation
    unsigned char empty_map[4096];

    // Write initialized maps to inode map and block map
    bwrite(0, empty_map);
    bwrite(1, empty_map);

    // Testing inode allocation
    int allocated_inode = ialloc();
    CTEST_ASSERT(allocated_inode != -1, "Allocate an inode");

    // Testing block allocation
    int allocated_block = alloc();
    CTEST_ASSERT(allocated_block != -1, "Allocate a block");

    // Prepare data for writing and then write to the allocated block
    unsigned char block_write[4096];
    for (size_t i = 0; i < sizeof(block_write); i++) {
        block_write[i] = (unsigned char)(i % 256);
    }
    bwrite(allocated_block, block_write);
    CTEST_ASSERT(bread(allocated_block, block_write) != NULL, "Write block and read back");

    // Test set_free and find_free functionality
    unsigned char free_block[4096];
    bread(1, free_block); 
    set_free(free_block, allocated_block, 0);  
    bwrite(1, free_block);
    int found_free = find_free(free_block);
    CTEST_ASSERT(found_free == allocated_block, "Free and find block");

    // Read back the data from the allocated block and verify
    unsigned char block_read[4096];
    bread(allocated_block, block_read);
    int blocks_match = 1;
    for (size_t i = 0; i < sizeof(block_read); i++) {
        if (block_read[i] != block_write[i]) {
            blocks_match = 0;
            break;
        }
    }
    CTEST_ASSERT(blocks_match, "Verify written block matches read block");

    // Test closing the image file
    CTEST_ASSERT(image_close() == 0, "Close image file");

    // Output test results
    CTEST_RESULTS();

    // Exit with the test status
    CTEST_EXIT();
}