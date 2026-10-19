#include <stdio.h>
#include <unistd.h>
#include <sys/reboot.h>

int main(void) {
    if (geteuid()) {
	fprintf(stderr, "please run as root\n");
	return 1;
    }

    sync();

#if defined(__linux__)
    if (reboot(RB_POWER_OFF) == -1) {
	return 1;
    }
#else
    if (reboot(RB_HALT | RB_POWERDOWN) == -1) {
	return 1;
    }
#endif
}
