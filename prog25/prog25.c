#include <stdio.h>
#include <stdlib.h>      
#include <unistd.h>      
#include <sys/wait.h>    
#include <sys/types.h>   

int main() {
    pid_t child_pids[3];
    int i;

    for (i = 0; i < 3; i++) {
        child_pids[i] = fork();
        if (child_pids[i] == 0) {
            sleep(i + 1); 
            exit(0);
        }
    }

    pid_t target_pid = child_pids[1];

    printf("\nparent is waiting for child with p_id: %d.\n", target_pid);
    waitpid(target_pid, NULL, 0);
    printf("Parent is now exiting.\n");

    return 0;
}

