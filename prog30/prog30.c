#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>

int main(int argc, char *argv[]) {
    // --- 1. Calculate the scheduled time ---
    time_t now_epoch;
    time(&now_epoch); // Get current time
    struct tm *deadline_tm = localtime(&now_epoch); // Convert to a struct

    // Overwrite with the user's target time from command line
    deadline_tm->tm_hour = atoi(argv[1]);
    deadline_tm->tm_min = atoi(argv[2]);
    deadline_tm->tm_sec = 0;

    // Convert the target time back into seconds since the epoch
    time_t deadline_epoch = mktime(deadline_tm);

    // --- 2. Daemonize the process ---
    if (fork() > 0) exit(EXIT_SUCCESS); // Parent exits
    setsid();                           // Child becomes session leader
    if (fork() > 0) exit(EXIT_SUCCESS); // First child exits
    
    // Grandchild (daemon) continues...
    chdir("/");                         // Change to a safe directory
    close(STDIN_FILENO);                // Close standard file descriptors
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    // --- 3. Wait for the scheduled time ---
    double seconds_to_wait = difftime(deadline_epoch, time(NULL));
    
    if (seconds_to_wait > 0) {
        sleep((unsigned int)seconds_to_wait);
        
        // --- 4. Execute the script ---
        system("/tmp/task_script.sh");
    }

    return 0;
}
