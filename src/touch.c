/* i gotta remember that argv[0] means the program name,
   while argv[1] means no args were passed or sum */

#include <stdio.h>
#include <utime.h>

void show_usage(void) {
    puts("Updates files to the current time");
    puts("Or can be used to create new files");
    printf("\n");

    puts("Returns 0 if passed");
    puts("Returns 1 if failed");
}

int main(int argc, char *argv[]) {
    if (argc == 1) {
	printf("usage: %s [options] <filename>\n", argv[0]);
	show_usage();
	return 1;
    }

    FILE *file_update = fopen(argv[1], "r");
    if (file_update != NULL) {
	if (utime(argv, NULL) == -1) {
	    fclose(file_update);
	    return 1;
	}
	fclose(file_update);
    } else {
        FILE *file_create = fopen(argv[1], "w");

        if (file_create == NULL) {
	    return 1;
        }

        fclose(file_create);
    }
    return 0;
}
