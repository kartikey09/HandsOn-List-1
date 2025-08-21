#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(){
	int fd;
	char* file_name = "my_file.txt";

	fd = creat(file_name, 0644);
	if(fd == -1){
		perror("Something went wrong while creating the file");
		exit(EXIT_FAILURE);
	}

	printf("File '%s' was created successfully.\n", file_name);
    	printf("The file descriptor value is: %d\n", fd);

	close(fd);
	return 0;
}


