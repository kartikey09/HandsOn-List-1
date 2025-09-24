#include <stdio.h>
#include <sched.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    pid_t pid = getpid();
    int current_policy;
    struct sched_param params;

 
    current_policy = sched_getscheduler(pid);
    printf("Initial policy is- ");
    switch (current_policy) {
        case SCHED_OTHER: printf("SCHED_OTHER\n"); break;
        case SCHED_FIFO:  printf("SCHED_FIFO\n"); break;
        case SCHED_RR:    printf("SCHED_RR\n"); break;
        default:          printf("Unknown\n"); break;
    }


    printf("\nset policy to SCHED_FIFO\n");
   
    params.sched_priority = 10; 
    sched_setscheduler(pid, SCHED_FIFO, &params);

    current_policy = sched_getscheduler(pid);
    printf("Current policy is now- ");
    switch (current_policy) {
        case SCHED_OTHER: printf("SCHED_OTHER\n"); break;
        case SCHED_FIFO:  printf("SCHED_FIFO\n"); break;
        case SCHED_RR:    printf("SCHED_RR\n"); break;
        default:          printf("Unknown\n"); break;
    }

    printf("\nset policy to SCHED_RR\n");
    params.sched_priority = 15; 
    sched_setscheduler(pid, SCHED_RR, &params);

    current_policy = sched_getscheduler(pid);
    printf("current policy is finally- ");
    switch (current_policy) {
        case SCHED_OTHER: printf("SCHED_OTHER\n"); break;
        case SCHED_FIFO:  printf("SCHED_FIFO\n"); break;
        case SCHED_RR:    printf("SCHED_RR\n"); break;
        default:          printf("Unknown\n"); break;
    }

    return 0;
}
