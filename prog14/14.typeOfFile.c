#include <stdio.h>
#include <stdint.h> // For uint64_t
#include <stdlib.h> // For exit()
#include <unistd.h> // For getpid()
#include <time.h>   // For clock_gettime()

/**
 * This program measures the time taken to execute the getpid() system call
 * using the high-resolution POSIX clock.
 *
 * This version is portable and works on various architectures.
 *
 * NOTE: On some older systems, you may need to link with the real-time
 * library by adding the -lrt flag during compilation:
 * gcc getpid_tsc.c -o getpid_tsc -lrt
 */

int main() {
    struct timespec start_time, end_time;
    pid_t pid;

    // 1. Get the time just before the system call.
    // CLOCK_MONOTONIC is a clock that cannot be set and represents monotonic
    // time since some unspecified starting point.
    if (clock_gettime(CLOCK_MONOTONIC, &start_time) == -1) {
        perror("clock_gettime start");
        exit(EXIT_FAILURE);
    }

    // 2. Execute the system call we want to measure.
    pid = getpid();

    // 3. Get the time immediately after the system call.
    if (clock_gettime(CLOCK_MONOTONIC, &end_time) == -1) {
        perror("clock_gettime end");
        exit(EXIT_FAILURE);
    }

    // 4. Calculate the difference in nanoseconds.
    uint64_t nanoseconds_taken = (end_time.tv_sec - start_time.tv_sec) * 1000000000L +
                                 (end_time.tv_nsec - start_time.tv_nsec);

    printf("The process ID is: %d\n", pid);
    printf("The getpid() system call took %llu nanoseconds.\n", (unsigned long long)nanoseconds_taken);

    return 0;
}


