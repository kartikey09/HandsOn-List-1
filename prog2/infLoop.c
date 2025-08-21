#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

//	run the prog as "./2a &" to run the process in backgroud and to end the process
//	use "kill <PID>" command to kill the process, find the PID using "ps -aur | grep 2a" command.

int is_pid_folder(char* name){
	for(int i = 0; name[i] != '\0'; i++){
		if(!isdigit(name[i]))
			return 0;
	}
	return 1;
}

void print_process_info(char* pid){
	char path[256];
	FILE* fp;
	char line[256];
	
	snprintf(path, sizeof(path), "/proc/%s/status", pid);
	fp = fopen(path, "r");
	if(fp == NULL)
		return;

	printf("----------------------------------\n");
	printf("Process ID (PID): %s\n", pid);
	
	while (fgets(line, sizeof(line), fp)) {
        if (strncmp(line, "Name:", 5) == 0 ||
            strncmp(line, "PPid:", 5) == 0 ||
            strncmp(line, "State:", 6) == 0) {
            printf("%s", line);
        }
    }

    fclose(fp);
}

int main(){
	DIR *proc_dir;
	struct dirent *entry;

	printf("Starting process monitor...\n");
	int flag = 1;
	while(1){
		proc_dir = opendir("/proc");
		if(proc_dir == NULL){
			perror("Something went wrong while opening the /proc directory");
			exit(EXIT_FAILURE);
		}
		
		printf("\n\n==== Scanning /proc for processes ====\n\n");

		while((entry = readdir(proc_dir)) != NULL){
			if(entry->d_type == DT_DIR && is_pid_folder(entry->d_name))
				print_process_info(entry->d_name);
		}

		closedir(proc_dir);

		printf("\n\n==== Scan finished, waiting for 5 seconds...  ====\n\n");
		sleep(5);

	}
	return 0;
}
