#include <stdio.h>

int main(int argc, char *argv[]) {
    for (int i = 1; i < argc; i++) {
	printf("%s", argv[1]);
	if (i < argc - 1) {
	    printf(" ");
	}
    }

    printf("\n");
    return 0;
}
