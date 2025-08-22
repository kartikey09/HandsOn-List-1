#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h> 
#include <unistd.h>
#include <string.h> 
#include <errno.h> 

int main(){
	const char* existing_file = "my_file.txt";
	const char* new_file = "new_file.txt";
	
	printf("\n--- Setup: Creating a file named '%s' ---\n", existing_file);

	int fd = open(existing_file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if(fd == -1){
		perror("Someting went wrong while creating a file");
		exit(EXIT_FAILURE);
	}	

	char* initial_content = "Hello this is the first line in my_file";
	write(fd, initial_content, strlen(initial_content));
	close(fd);
	printf("\n--- Setup complete. %s file has been created ----\n",existing_file);
	
	printf("\n\n--- CASE 1: opening an exiting file in read write mode ----\n\n");

	fd = open(existing_file, O_RDWR);
	if(fd == -1){
		printf("could not open the file %s", existing_file);
		perror("open "); 
	} else {
		printf("Success, '%s' opened in read write mode. File descriptor: %d\n", existing_file, fd);
		close(fd);
	}

	printf("\n\n--- CASE 2: creating an existing file with O_CREAT | O_EXCL ----\n\n");

        fd = open(existing_file, O_RDWR | O_CREAT | O_EXCL, 0644);
        if(fd == -1){
                printf("could not open the file %s (Expected behaviour)", existing_file);
                perror("error details ");
        } else {
                printf("Unexpected behaviour, this should not have happened \n");
                close(fd);
        }

	printf("\n\n--- CASE 3: creating an new file with O_CREAT | O_EXCL ----\n\n");

        fd = open(new_file, O_RDWR | O_CREAT | O_EXCL, 0644);
        if(fd == -1){
                printf("Error could create a new file\n");
                perror("error details ");
        } else {
        	printf("Success, '%s' new file created becuase it did not exist already. File descriptor: %d\n",new_file, fd);
		close(fd);
        }

	printf("\n\n--- Cleanup: Removing created files ---\n\n");
    	remove(existing_file);
    	remove(new_file);
    	printf("Cleanup complete.\n");
	return 0;
}
