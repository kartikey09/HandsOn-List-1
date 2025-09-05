#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h> 
#include <time.h> 

int main(int argc, char *argv[]){

	if (argc != 2){
       		fprintf(stderr, "Not enough args");
        	exit(EXIT_FAILURE);
    	}

	char *filename = argv[1];

	struct stat file_stat;


	if (stat(filename, &file_stat) == -1) {
        	perror("Error getting file stat");
        	exit(EXIT_FAILURE);
   	}


    	// a. Inode number
    	printf("Inode number: \t\t%ld\n", (long)file_stat.st_ino);

    	// b. Number of hard links
    	printf("Number of hard links: \t%ld\n", (long)file_stat.st_nlink);

    	// c. User ID of the owner
    	printf("User ID (UID): \t\t%d\n", file_stat.st_uid);

    	// d. Group ID of the owner
    	printf("Group ID (GID): \t\t%d\n", file_stat.st_gid);

  	// e. Total size of the file, in bytes
    	printf("Size: \t\t\t%ld bytes\n", (long)file_stat.st_size);

    	// f. Preferred block size for I/O
    	printf("Block size: \t\t%ld bytes\n", (long)file_stat.st_blksize);

    	// g. Number of 512B blocks allocated
    	printf("Number of blocks: \t%lld\n", (long long)file_stat.st_blocks);

    	printf("\n--- Timestamps ---\n");
    	// h. Time of last access
    	// ctime() converts the time_t value to a human-readable string.	
	
    	printf("Last access time: \t%s", ctime(&file_stat.st_atime));

    	// i. Time of last modification (content change)
    	printf("Last modification time: \t%s", ctime(&file_stat.st_mtime));

    	// j. Time of last change (status/metadata change)
    	printf("Last status change time: \t%s", ctime(&file_stat.st_ctime));

	return 0;
}
