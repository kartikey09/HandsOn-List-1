#include <stdio.h>
#include <stdlib.h>
#include <sys/select.h> // For select(), fd_set, etc.
#include <sys/time.h>   // For struct timeval
#include <unistd.h>     // For STDIN_FILENO

int main(){

	fd_set read_fds;
	struct timeval timeout;
	int select_retval;

	FD_ZERO(&read_fds);
	
	FD_SET(STDIN_FILENO, &read_fds);

	timeout.tv_sec = 10;
	timeout.tv_usec = 0;

	printf("Waiting for input from STDIN for 10 seconds...\n");
    	printf("Please type something and press Enter: ");
    	fflush(stdout);

	select_retval = select(STDIN_FILENO + 1, &read_fds, NULL, NULL, &timeout);

	if(select_retval > 0 && FD_ISSET(STDIN_FILENO, &read_fds)){
           	printf("\n\nVerification: Data is available on STDIN within 10 seconds.\n");
        } else {
		printf("\n\nVerification: No data received within 10 seconds. Timeout occurred.\n");
	}

	return 0;
}
