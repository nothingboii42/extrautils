// i will show comments to explain now

#include <unistd.h>
#include <sys/reboot.h>
#include <stdio.h>

#define SYSTEM_HALT_CMD RB_HALT

int main(void) {
    // check for root
    if (geteuid()) {
        fprintf(stderr, "please run as root\n");
        return 1;
    }

    // flush filesystem buffers
    sync();

// check for os, because bsd and linux are different
#if defined(__linux__)
    #undef SYSTEM_HALT_CMD
    #define SYSTEM_HALT_CMD RB_HALT_SYSTEM
#elif defined(RB_POWERDOWN)
    #undef SYSTEM_HALT_CMD
    #define SYSTEM_HALT_CMD (RB_HALT | RB_POWERFOWN)
#endif

    // execute reboot system call
    if (reboot(SYSTEM_HALT_CMD) == -1) {
	return 1;
    }
}
