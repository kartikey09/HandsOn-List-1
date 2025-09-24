#include <stdio.h>

int main(int argc, char *argv[]) {
    printf("this program received %d arguments.\n", argc);

    for (int i = 0; i < argc; i++) {
        printf("\n  Argument %d: %s\n", i, argv[i]);
    }

    return 0;
}

