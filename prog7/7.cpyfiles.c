#include<stdlib.h>
#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>

#define BUFFER_SIZE  4096

int main(int argc, char* argv[]){
	
	if(argc != 3){
		fprintf(stderr, "not enough args");
		exit(EXIT_FAILURE);
	}

	char *source_file = argv[1];
	char *dest_file = argv[2];
		
	int source_fd = open(source_file, O_RDONLY, 0644);
	if(source_fd == -1){
		perror("Error opening source file");
		exit(EXIT_FAILURE);
	}

	int dest_fd = open(dest_file, O_WRONLY, O_TRUNC, O_CREAT, 0644);
	if(dest_fd == -1){
                perror("Error opening destination file");
		close(source_fd);
                exit(EXIT_FAILURE);
        }

	char buffer[BUFFER_SIZE];
	ssize_t bytes_read;

	while((bytes_read = read(source_fd, buffer, BUFFER_SIZE)) > 0){
		
		ssize_t bytes_written = write(dest_fd, buffer, bytes_read);

		if(bytes_written != bytes_read){
			perror("error writing to the destination file");
			close(source_fd);
			close(dest_fd);
			exit(EXIT_FAILURE);
		}
	}

	if(bytes_read < 0){
		perror("Error reading from the source file");
			close(source_fd);
                        close(dest_fd);
                        exit(EXIT_FAILURE);
	}

	printf("File copied successfully !");
	close(source_fd);
        close(dest_fd);
	return 0;
}

	
