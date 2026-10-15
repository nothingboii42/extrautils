#include <stdlib.h>

int main(void) {
    int status = system("echo $PWD");
    return status; // return status from system
}
