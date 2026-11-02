/* this has all of the shell options like verbose, trace mode, etc */

#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>

// from sh.c
extern char *name;

char *command = NULL;
size_t size = 0;

void block_int(void) {
    struct sigaction sa;
    sa.sa_handler = SIG_IGN;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    // block ctrl c and ctrl z
    sigaction(SIGINT, &sa, NULL);
    sigaction(SIGTSTP, &sa, NULL);
}

// interactive, but we dont know if its a login or non-login shell
void spawn_shell(char type[]) {
    /* D is for Default
       V is for verbose
       T is for trace mode */

    char *tokens[502];

    if (strcmp(type, "D") == 0) {
	block_int();
        while (1) {
	    if (geteuid()) {
                printf("$ ");
                fflush(stdout);
	    } else {
	        printf("# ");
		fflush(stdout);
	    }

	    // end of line shit
	    if (getline(&command, &size, stdin) == -1) {
		printf("\n"); // try to make it look natural
		printf("exit\n");
		free(command);
	        break;
	    }

	    int i = 0;
	    memset(tokens, 0, sizeof(tokens));

	    char *token = strtok(command, " \t\r\n");
	    while (token != NULL) {
		tokens[i++] = token;
		if (i >= 501) break;
		token = strtok(NULL, " \t\r\n");
	    }

	    tokens[i] = NULL;
	    if (tokens[0] != NULL) {
                if (strcmp(tokens[0], "exit") == 0) {
		    // exit, this checks if tokens 1 was null, if it is, it returns 0
		    if (tokens[1] == NULL) {
                        free(command);
                        command = NULL;
		        exit(0);
		    } else {
			free(command);
			command = NULL;
			exit(tokens[1]);
		    }
                } else if (strcmp(tokens[0], "cd") == 0) {
		    // if tokens[1] is NULL, chdir into the home directory
		    char *home = getenv("HOME");
                    if (tokens[1] == NULL) {
			if (home != NULL) {
			    if (chdir(home) == -1) {
			        fprintf(stderr, "%s: failed to chdir to home directory\n", name);
			    }
			}
		    } else { // tokens[1] exists
		        if (chdir(tokens[1]) == -1) {
			    perror("cd");
			}
		    }
		} else if (strcmp(tokens[0], "#") == 0) {
		    ; // do nothing because its a comment
		} else if (strcmp(tokens[0], ":") == 0) {
		    ; // do nothing again because its a placeholder
                } else {
		    // we are now gonna fork
		    pid_t pid = fork();
		    if (pid < 0) {
			fprintf(stderr, "%s: failed to fork\n", name);
			exit(1);
		    } else if (pid == 0) {
			execvp(tokens[0], tokens);
			// if execvp returns, the command was not found
			printf("%s: command not found: %s\n", name, tokens[0]);
			_exit(127);
		    } else {
			// parent process waits for command
			wait(NULL);
		    }
	        }
	    }
	    free(command);
	    command = NULL;
	    size = 0;
	}
    } else if (strcmp(type, "V") == 0) {
	if (geteuid()) {
	    printf("$ ");
	    fflush(stdout);
	} else {
	    printf("# ");
	    fflush(stdout);
	}
    }
}
