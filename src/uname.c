#include <sys/utsname.h>
#include <stdio.h>
#include <getopt.h>

int main(int argc, char *argv[]) {
    struct utsname b;
    int command_arg;
    int options = 0;

    if (uname(&b) != 0) {
	fprintf(stderr, "uname system call failed\n");
	return 1;
    }

    if (argc == 1) {
        printf("%s\n", b.sysname);
    }

    struct option long_cmd[] = {
        {"all", no_argument,       NULL, 'a'},
	{"node", no_argument,	   NULL, 'n'},
	{"release", no_argument,   NULL, 'r'},
	{"version", no_argument,   NULL, 'v'},
	{"machine", no_argument,   NULL, 'm'},
	{"help", no_argument,	   NULL, 'h'},
	{0,         0,                 0,  0 }
    };

    while ((command_arg = getopt_long(argc, argv, "anrvmh", long_cmd, &options)) != -1) {
	switch (command_arg) {
	    case 'a':
		printf("%s, %s, %s, %s, %s\n", b.sysname, b.nodename, b.release, b.version, b.machine);
		break;
	    case 'n':
		printf("%s\n", b.nodename);
		break;
	    case 'r':
		printf("%s\n", b.release);
		break;
	    case 'm':
		printf("%s\n", b.machine);
		break;
	    case 'v':
		printf("%s\n", b.version);
		break;
	    case 'h':
		puts("uname - Display info about your system");
    		printf("usage: %s <options>\n", argv[0]);
    		puts("    -a --all: Display all information");
    		puts("    -n --node: Display node name");
    		puts("    -r --release: Kernel release");
    		puts("    -v --version: Kernel version");
    		puts("    -m --machine: Display machine");
    		puts("    -h --help: Show this help");
		return 0;
	    case '?':
		printf("use -h or --help for help\n");
		return 1;
	    defualt:
		return 1;
	}
    }
    return 0;
}
