#include <stdio.h>
#include <stdint.h> 
#include <unistd.h> 


static inline uint64_t timer() {
    uint64_t val;
    __asm__ __volatile__ ("mrs %0, cntvct_el0" : "=r"(val));
    return val;
}

int main() {
    uint64_t start, end;
    pid_t pid;

    start = timer();
    pid = getpid();
    end = timer();
    uint64_t time = end - start;

    printf("the process ID is: %d\n", pid);
    printf("time taken: %llu.\n", (unsigned long long)time);

    return 0;
}


