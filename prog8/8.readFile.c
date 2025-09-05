#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
	
	if(argc != 2){
		fprintf(stderr, "not enough args");
		exit(EXIT_FAILURE);
	}
	
	char *filename = argv[1];
	FILE *file = fopen(filename, "r");

	if(file == NULL){
		printf("Error opening file");
		exit(EXIT_FAILURE);
	}
	
	char buffer[1024];
	
	while(fgets(buffer, sizeof(buffer), file) != NULL)
		printf("%s", buffer);

	fclose(file);
	return 0;
}
	       	



