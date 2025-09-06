#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>   
#include <fcntl.h>   
#include <string.h>

int main(int argc, char* argv[]){
	
	if(argc != 2){
		perror("Not enough arguments");
		exit(EXIT_FAILURE);
	}

	char *filename = argv[1];

	mode_t mode = 0666; 
	int fd1 = open(filename, O_RDWR | O_TRUNC | O_CREAT, mode);
	
	if(fd1 == -1){
		perror("Error opening/ creating file");
		exit(EXIT_FAILURE);
	}

	char* buffer1 = "0123456789";
	ssize_t bytes_written  = write(fd1, buffer1, strlen(buffer1));  
	if(bytes_written == -1){
		perror("\nError in writing initial data ");
		close(fd1);
		exit(EXIT_FAILURE);
	}
	
	printf("Wrote %ld bytes of data, current offset is at %ld. \n", (long)bytes_written, (long)lseek(fd1, 0, SEEK_CUR));

	printf("\n-------- Seeking 10 bytes of empty space  --------\n");
	
	off_t offset = lseek(fd1, 10, SEEK_CUR);
	
	if(offset == 0){
		perror("\nError in seeking");
		close(fd1);
		exit(EXIT_FAILURE);
	}

	printf("\nSeek successful, new offset is at %ld.\n", (long)offset);

	char *buffer2 = "ABCDEFGHIJ";
	bytes_written = write(fd1, buffer2, strlen(buffer2));
	if(bytes_written < 0){
		perror("\nError while writing buffer2 to file");
		close(fd1);
		exit(EXIT_FAILURE);
	}

	printf("\nWrote another %ld bytes of data, current offset is at %ld.\n", (long)(bytes_written), (long)lseek(fd1, 0, SEEK_CUR));
	close(fd1);
	printf("use 'od -c %s' to inspect its content\n\n", filename);
	return 0;
}
