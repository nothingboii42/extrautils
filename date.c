#include <stdio.h>
#include <time.h>

int main(int argc, char *argv[]) {
    time_t date;
    time(&date);

    printf("%s", ctime(&date));
    return 0;
}
