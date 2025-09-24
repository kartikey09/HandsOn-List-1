#include <stdio.h>
#include <sched.h> 

int main() {
    printf("max priority: %d\n", sched_get_priority_max(SCHED_FIFO));
    printf("min priority: %d\n", sched_get_priority_min(SCHED_FIFO));

    return 0;
}

