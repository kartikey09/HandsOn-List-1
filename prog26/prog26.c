#include <stdio.h>
#include <unistd.h> // Required for the execl() function

int main() {

    execl("./target", "target", "Kartikey", NULL);

return 1;
}
