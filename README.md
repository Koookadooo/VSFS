# Simulated File System Project

## Building

**Command line:**

- `make` to build the project. This will produce an executable called `testfs`.
- `make test` to build and run the project. Produces and executes `testfs`

## Using the executable:

To run the simulation:

- The executable does not require command line arguments but relies on a predefined test image file named `test.img`.

**Example:** `./testfs`

This command runs the program which tests the functionality of opening, writing to, reading from, and closing a simulated file system image.

## Files

- `testfs.c`: Main program source file that includes tests for file system operations.
- `block.c`: Contains the definitions of functions to manage data blocks within the file system image.
- `block.h`: Header file for `block.c` with function declarations and constants.
- `image.c`: Manages the file system image file including opening and closing operations.
- `image.h`: Header file for `image.c` which includes function declarations and the file descriptor.
- `free.c`: Contains functions for managing the free space bitmap of the file system.
- `free.h`: Header file for `free.c` with declarations related to free space management.
- `inode.c`: Contains functions specifically for managing inodes within the file system.
- `inode.h`: Header file for `inode.c` which includes inode management function declarations.
- `Makefile`: File which builds the executable and handles cleaning operations.

## Data

This program simulates file system operations by manipulating data blocks within a single large file (`test.img`), mimicking the behavior of a block-based file system:

- Data is managed in blocks of 4096 bytes.
- Each operation on blocks is encapsulated through the `block.c` implementations.

## Functions

**Overview of functions and their hierarchy:**

### `main()`

- Executes a series of file system operations including opening, writing to, reading from, and closing the file system image.
- Validates the correctness of each operation and prints test results.

### `image_open(char *filename, int truncate)`

- Opens or creates (with optional truncation) the file system image file.

### `image_close()`

- Closes the file system image file.

### `bwrite(int block_num, unsigned char *block)`

- Writes a block of data to a specified block number in the file system image.

### `bread(int block_num, unsigned char *block)`

- Reads a block of data from a specified block number in the file system image.

### `ialloc()`

- Allocates a previously-free inode from the inode bitmap and returns its index.

### `alloc()`

- Allocates a previously-free data block from the block bitmap and returns its index.

### `set_free(unsigned char *block, int num, int set)`

- Sets or clears a specific bit in the block to mark it as free or used.

### `find_free(unsigned char *block)`

- Finds the first free bit in the block and returns its index.

## Notes

- The project serves as a basic demonstration of how file system operations like block reading and writing can be simulated in user space.
- This simulation helps in understanding the lower-level workings of file systems without the need to interact directly with disk hardware.

## Cleaning Up

- `make clean`: Removes all compiled object files and temporary files.
- `make pristine`: Removes all compiled object files, the executable, and static libraries (`libvvsfs.a`), ensuring a clean state for a complete rebuild.
