#include <stdio.h>
#include <unistd.h> 
#include <sys/types.h> 

int main() {

    pid_t pid = fork();

    if (pid == 0) {

        printf("Child Process:\n");
        printf("child PID is: %d\n", getpid());
    } else {

        printf("Parent Process: \n");
        printf("parent PID is: %d\n", getpid());
    }

    return 0;
}

