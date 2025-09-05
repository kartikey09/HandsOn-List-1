#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>


int BUFFER_SIZE = 1024;

int main(){
	char buffer[BUFFER_SIZE];

	ssize_t bytes_read;

	while((bytes_read = read(0, buffer, BUFFER_SIZE)) > 0){
		
		ssize_t bytes_written = write(1, buffer, bytes_read);
		if(bytes_written != bytes_read){
			perror("Error occured ");
			exit(EXIT_FAILURE);
		}

	}

	if(bytes_read < 0){
		perror("Error occured while reading the STDIN ");
		exit(EXIT_FAILURE);
	}

	return 1;
}



