#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h> 
#include <unistd.h>   


int main(int argc, char *argv[]) {
    // a. Input should be taken from command line.
    if (argc != 2) {
        fprintf(stderr, "not enough args");
        exit(EXIT_FAILURE);
    }

    const char *path = argv[1];
    struct stat file_stat;

    lstat(path, &file_stat);

    printf("type is- %s\n", path);
    
    mode_t mode = file_stat.st_mode;

    if (S_ISREG(mode)) {
        printf("Regular File\n");
    } else if (S_ISDIR(mode)) {
        printf("Directory\n");
    } else if (S_ISLNK(mode)) {
        printf("Symbolic Link\n");
    } else if (S_ISCHR(mode)) {
        printf("Character Device\n");
    } else if (S_ISBLK(mode)) {
        printf("Block Device\n");
    } else if (S_ISFIFO(mode)) {
        printf("FIFO (Named Pipe)\n");
    } else if (S_ISSOCK(mode)) {
        printf("Socket\n");
    } else {
        printf("Unknown Type\n");
    }

    return 0;
}
