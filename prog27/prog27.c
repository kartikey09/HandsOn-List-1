#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>      
#include <sys/wait.h>    

int main() {
    printf("\na. execl\n");
    execl("/bin/ls", "ls", "-Rl", NULL);

    printf("\nb. execlp\n");
    execlp("ls", "ls", "-Rl", NULL);

    printf("\nc. execle\n");
    extern char **environ;
    execle("/bin/ls", "ls", "-Rl", NULL, environ);

    printf("\nd. execv\n");
    char *args[] = {"ls", "-Rl", NULL};
    execv("/bin/ls", args);

    printf("\ne. Demonstrating execvp ---\n");
    char *args2[] = {"ls", "-Rl", NULL};
    execvp("ls", args2);
    return 0;
}
