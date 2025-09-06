#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h> // Contains fcntl() and the O_* flags
		  
int main(int argc, char *argv[]){

	if(argc != 2){
		perror("Not enough args");
		exit(EXIT_FAILURE);
	}

	char *filename = argv[1];
	int fd = open(filename, O_RDWR | O_CREAT | O_APPEND, 0666);
	if(fd == -1){
		perror("Error opening the file");
		exit(EXIT_FAILURE);
	}

	int flags = fcntl(fd, F_GETFL);
	int access_mode = flags & O_ACCMODE;

	if (access_mode == O_RDONLY) {
        	printf("Access Mode: Read Only (O_RDONLY)\n");
    	} else if (access_mode == O_WRONLY) {
        	printf("Access Mode: Write Only (O_WRONLY)\n");
    	} else if (access_mode == O_RDWR) {
        	printf("Access Mode: Read-Write (O_RDWR)\n");
    	} else {
        	printf("Access Mode: Unknown\n");
    	}


	if (flags & O_APPEND) {
        	printf("Status Flag: Append mode is ON (O_APPEND)\n");
    	} else {
        	printf("Status Flag: Append mode is OFF\n");
    	}

	close(fd);
	return 0;
}




