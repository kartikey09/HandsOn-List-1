#include <stdio.h>
#include <stdlib.h>      
#include <unistd.h>      
#include <sys/types.h>   

int main() {
    pid_t pid = fork();
    if (pid > 0) {
        printf("Parent Process PID: %d is running.\n", getpid());
        printf("Child process PID: %d is now a zombie.\n", pid);
        sleep(2);
        printf("Parent is exiting.\n");
    } else {
        printf("Child Process PID: %d is exiting now.\n", getpid());
        exit(0);
    }

    return 0;
}
