#include <stdlib.h>

int main(void) {
    int status = system("echo $HOME");
    return status;
}
