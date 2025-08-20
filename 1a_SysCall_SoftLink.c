// File: create_softlink.c
// Description: This program demonstrates how to create a soft link (symbolic link)
// using the symlink() system call in C.
//
// To compile and run:
// 1. gcc create_softlink.c -o create_softlink
// 2. ./create_softlink
// 3. ls -l target.txt soft_link.txt  (to verify the link was created)

#include <stdio.h>
#include <unistd.h> // Required for symlink()
#include <stdlib.h> // Required for exit()
#include <fcntl.h>  // Required for open() and file creation flags

int main() {
    const char* target_file = "target.txt";
    const char* link_name = "soft_link.txt";

    // 1. First, create a target file to link to.
    // We use open() with O_CREAT to ensure the file exists.
    int fd = open(target_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("Error creating target file");
        exit(EXIT_FAILURE);
    }
    // Write some content to it.
    write(fd, "Hello, world!", 13);
    close(fd);
    printf("Successfully created target file: '%s'\n", target_file);

    // 2. Now, create the soft link using the symlink() system call.
    // The first argument is the path the link will point to.
    // The second argument is the name of the link file itself.
    if (symlink(target_file, link_name) == -1) {
        // perror() is useful for printing system call error messages.
        perror("Error creating soft link");
        exit(EXIT_FAILURE);
    }

    printf("Successfully created soft link: '%s' -> '%s'\n", link_name, target_file);

    return 0;
}

