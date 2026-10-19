#include <unistd.h>
#include <sys/reboot.h>
#include <stdio.h>

int main(void) {
    if (geteuid()) {
	fprintf(stderr, "please run as root\n");
	return 1;
    }

    sync();
    if (reboot(RB_AUTOBOOT) == -1) {
	return 1; // it failed
    }
}
