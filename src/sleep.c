#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
	printf("usage: %s <seconds>\n", argv[0]);
	return 1;
    }

    int seconds = atoi(argv[1]);

    if (seconds <= 0) {
	printf("please make sure number is higher than 0\n");
	return 1;
    }

    sleep(seconds);
    return 0;
}
