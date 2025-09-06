#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>   // For write(), close(), dup(), dup2()
#include <fcntl.h>    // For open(), fcntl() and its flags
#include <string.h>   // For strlen()
		      
int main(int argc, char* argv[]){
	
	if(argc != 2){
		fprintf(stderr, "Not enough arguments");
		exit(EXIT_FAILURE);
	}
		
	char *filename = argv[1];
	mode_t mode = 0666;
	int original_fd = open(filename, O_CREAT | O_TRUNC | O_WRONLY, mode);

	if(original_fd < 0){
		perror("Error opening original file");
		exit(EXIT_FAILURE);
	}

	char *original_content = "\nthis is the original content\n";
	char *dup_content = "\nthis is the dup() content\n";
	char *dup2_content = "\nthis is the dup2() content\n";
	char *fcntl_content = "\nthis is the fcntl() content\n";

	if(write(original_fd, original_content, strlen(original_content)) < 0){
		perror("Error while putting original content");
		close(original_fd);
		exit(EXIT_FAILURE);
	}

	printf("\n Successfully written using original_fd\n");

	int dup_fd = dup(original_fd);
	if(dup_fd < 0){
		perror("Error creating dup_fd");
		close(original_fd);
		exit(EXIT_FAILURE);
	}
	
	
	write(dup_fd, dup_content, strlen(dup_content));
	close(dup_fd);

	printf("\n Successfully written using dup_fd\n");

	int dup2_fd = dup2(original_fd, 10);

	if(dup2_fd < 0){
		perror("Error creating dup2_fd");
		close(original_fd);
		exit(EXIT_FAILURE);
	}

	write(dup2_fd, dup2_content, strlen(dup2_content));
	close(dup2_fd);

	printf("\n Successfully written using dup2_fd\n");

	int fcntl_fd = fcntl(original_fd, F_DUPFD, 20);
	
	if(fcntl_fd < 0){
		perror("Error creating fcntl_fd");
		close(original_fd);
		exit(EXIT_FAILURE);
	}

	write(fcntl_fd, fcntl_content, strlen(fcntl_content));
	close(fcntl_fd);

	printf("\n Successfully written using fcntl_fd\n");

	close(original_fd);
	return 0;
}




