#include <stdio.h>
#include <unistd.h> // For nice()
#include <stdlib.h> // For atoi()

int main(int argc, char *argv[]) {
    int curr_p= nice(0);
    printf("Initial nice value: %d\n", curr_p);

    if (argc > 1) {
        int inc = atoi(argv[1]);
        int new_p = nice(inc);
        printf("new nice value is: %d\n", new_p);
    }
    return 0;
}
