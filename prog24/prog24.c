#include <stdio.h>
#include <unistd.h>     
#include <sys/types.h>  

int main() {
    pid_t pid = fork();

    if (pid > 0) {
        printf("Parent Process PID: %d.\n", getpid());
    } else {
        printf("Child Process PID: %d is running.\n", getpid());
        printf("Child's initial Parent PID: %d\n", getppid());
        sleep(2);
        printf("\nChild woke up.\n");
        printf("Child's new Parent PID is now: %d\n", getppid());
    }
    return 0;
}
