#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

int main(){
	const char* target_file = "target.txt";
	const char* link_file = "link.txt";

	int fd = open(target_file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if(fd == -1){
		perror("Error while creating the target file");
		exit(EXIT_FAILURE);
	}

	char* text = "Hello this is the first line in the target file";
	write(fd, text, strlen(text));
	close(fd);
	printf("Target file created successfully : \n %s \n", target_file); 

	if(symlink(target_file, link_file) == -1){
		perror("Error while creating soft link");
		exit(EXIT_FAILURE);
	}

	printf("soft link successfully created '%s' ---> '%s'\n", link_file, target_file);
	return 0;
}	
