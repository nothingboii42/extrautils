#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc == 1) {
        puts("Extrautils Project v0.0.1");
	puts("A simple program that executes Extrautils binaries");
	puts("Commands:");
	puts("		{clear}, {echo}, {home}, {pwd}, {sleep}, {uname}, {whoami}");
	puts("		{date}, {arch}, {halt}, {poweroff}, {reboot}, {env}");
	return 1;
    }

    int status = system(argv[1]);
    return status;
}
