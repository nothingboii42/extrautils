// sh - a shell for extrautils
// this was rushed so dont expect this to be good

#include <stdio.h>
#include "shell.h"
#include <getopt.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

// program name
char *name = NULL;

void show_usage(void) {
    puts("    -c: execute command");
    puts("    -h, --help: show this help");
    puts("    -v, --verbose: print whats happening");
    puts("    -x: trace mode");
    puts("    --login: login mode");
}

// the file opening isn't complete, i will fix this
int main(int argc, char *argv[]) {
    name = argv[0];
    if (argc == 2) {
	FILE *file = fopen(argv[2], "r"); // open file and read only
	if (file == NULL) {
	    ;
	}
    }

    // parse some args, but not all, or else it will be eugh
    if (argc > 1 && strcmp(argv[1], "-c") == 0) {
        if (argv[2] == NULL) {
	    printf("no command was detected (work in progress)\n");
	    return 1;
	}

	pid_t pid = fork();
	if (pid < 0) {
            fprintf(stderr, "%s: failed to fork\n", name);
            exit(1);
        } else if (pid == 0) {
	    char *args[64] = {NULL}; // put NULL because its good
	    int i = 0;

	    if (argv == NULL) {
		fprintf(stderr, "%s: -c requires an command\n", name);
		exit(2);
	    }

	    char *token = strtok(argv[2], " ");
	    while (token != NULL && i < 63) {
		args[i++] = token;
		token = strtok(NULL, " ");
	    }
	    args[i] = NULL;

	    // make sure that there is no empty string
	    if (args == NULL) {
		exit(0);
	    }

            execvp(args[0], args);
	    perror("sh");
            // if execvp returns, the command was not found
            printf("%s: command not found: '%s'\n", name, args[0]);
            exit(127);
        } else {
            // parent process waits for command
            wait(NULL);
        }
    } else if (argc > 1 && strcmp(argv[1], "-h") == 0) {
	printf("usage: %s [options] <file.sh>\n");
	show_usage();
	return 0;
    } else if (argc > 1 && strcmp(argv[1], "--help") == 0) {
	printf("usage: %s [options] <file.sh>\n");
	show_usage();
	return 0;
    }

    if (argc == 1) {
	spawn_shell("D");
    }
}
