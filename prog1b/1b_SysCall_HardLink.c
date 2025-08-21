#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main(){
	const char* target_file = "target.txt";
	const char* link_file = "hardLink.txt";

	int fd = open(target_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if(fd == -1){
		perror("Something went wrong while creating the target file");
		exit(EXIT_FAILURE);
	}
	
	char* text = "This is the first line in hardlink file";
	write(fd, text, strlen(text));
       	close(fd);

	printf("Successfully created target file: '%s'\n", target_file);
	
	if(link(target_file, link_file) == -1){
		perror("Something went wrong while hard linking file");
		exit(EXIT_FAILURE);
	}

	printf("Successfully created hard link: '%s' for '%s'\n", link_file, target_file);
}

