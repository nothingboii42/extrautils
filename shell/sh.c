// sh - a shell for extrautils

#include <stdio.h>
#include "shell.h"

// program name
char *name = NULL;

// the file opening isn't complete, i will fix this
int main(int argc, char *argv[]) {
    name = argv[0];
    if (argc == 2) {
	FILE *file = fopen(argv[2], "r"); // open file and read only
	if (file == NULL) {
	    ;
	}
    }

    if (argc == 1) {
	spawn_shell("D");
    }
}
