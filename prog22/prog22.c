#include <stdio.h>
#include <unistd.h>      
#include <fcntl.h>       
#include <string.h>      
#include <sys/types.h> 

int main() {
    int fd = open("shared_output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0666);
    pid_t pid = fork();

    if(pid == 0){
        const char *child_msg = "child process here.\n";
        write(fd, child_msg, strlen(child_msg));
    } else {
        const char *parent_msg = "parent process here.\n";
        write(fd, parent_msg, strlen(parent_msg));
    }

    close(fd);
    printf("Program finished. Check the contents of 'shared_output.txt'.\n");

    return 0;
}
