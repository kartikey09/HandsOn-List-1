#include <fcntl.h>  // Import for `creat` system call
#include <stdio.h>      // Import printf

int main(){
        int fd1 = creat("test1.txt",0644);
        int fd2 = creat("test2.txt",0644);
        int fd3 = creat("test3.txt",0644);
        int fd4 = creat("test4.txt",0644);
        int fd5 = creat("test5.txt",0644);
        printf("File Descriptors: %d %d %d %d %d", fd1, fd2, fd3, fd4, fd5);
        printf("\nAll files created and remain open.\n");
        printf("Program now running an infinite loop.\n");
        while(1);
        return 0;
}
