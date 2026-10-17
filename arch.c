#include <sys/utsname.h>
#include <stdio.h>

int main(void) {
    struct utsname arch;

    if (uname(&arch) != 0) {
	fprintf(stderr, "uname system call failed\n");
	return 1;
    }

    printf("%s\n", arch.machine);
    return 0;
}
