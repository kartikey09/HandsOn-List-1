#include <stdio.h>
#include <sys/types.h> // Required for mkfifo()
#include <sys/stat.h>  // Required for mkfifo() and permission macros
#include <stdlib.h>    // Required for exit()
#include <unistd.h>    // Required for unlink()

int main(){
	const char* fifo_name = "my_fifo";
	mode_t fifo_mode = 0666;
	unlink(fifo_name);

	if(mkfifo(fifo_name, fifo_mode) == -1){
		perror("Something went wrong while creating the FIFO file");
		exit(EXIT_FAILURE);
	}
	
	printf("FIFO file %s created successfuly!", fifo_name);
	return 0;
}
