/* Init system for extrautils, systemd is bloat so yeah */

// nobody views this project so idc, still gonna make it

#include <unistd.h>
#include <stdio.h>
#include <sys/mount.h>
#include <string.h>
#include <sys/reboot.h>

#define SYSTEM_HALT_CMD RB_HALT

int poweroff(void) {
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

int halt(void) {
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

void show_usage(void) {
    puts("Init system");
    printf("\n");
    puts("    --help: Show this help");
    puts("    halt: Halt the device");
    puts("    poweroff: Poweroff the device");
    puts("    reboot: Reboot the device");
    printf("\n");
    puts("If you type unknown arguments, it will ignore it");
}

int main(int argc, char *argv[]) {
    // options like reboot, poweroff, halt, --help
    if (argc > 1 && strcmp(argv[1], "reboot") == 0) {
	if (geteuid()) {
	    fprintf(stderr, "%s: Permission Denied\n", argv[0]);
	    return 1;
	}

	sync();
	if (reboot(RB_AUTOBOOT) == -1) {
            return 1; // it failed
        }
    } else if (argc > 1 && strcmp(argv[1], "poweroff") == 0) {
	if (geteuid()) {
            fprintf(stderr, "%s: Permission Denied\n", argv[0]);
            return 1;
        }

	sync();
	poweroff();
	return poweroff; // hope it didnt fail
    } else if (argc > 1 && strcmp(argv[1], "halt") == 0) {
	if (geteuid()) {
            fprintf(stderr, "%s: Permission Denied\n", argv[0]);
            return 1;
        }

	sync();
	halt();
	return halt; // hope this also didnt fail
    } else if (argc > 1 && strcmp(argv[1], "--help") == 0) {
	printf("usage: %s [options]\n", argv[0]);
	show_usage();
        return 0;
    }

    // what pid are you init?
    if (getpid() != 1) {
	fprintf(stderr, "%s: must be running as PID 1!\n", argv[0]);
	return 1;
    }

    // parent id?
    if (getppid() != 0) {
	fprintf(stderr, "%s: must be running as Parent ID 0!\n", argv[0]);
	return 1;
    }

    // looks like we are parent id 0 and pid 1

    mkdir("/proc", 0755);
    mkdir("/sys", 0755);
    mkdir("/dev", 0755);
    mkdir("/run", 0755);

    if (mount("proc", "/proc", "proc", 0, NULL) < 0) {
	fprintf(stderr, "ERROR: Failed to mount /proc\n");
    }

    if (mount("sysfs", "/sys", "sysfs", 0, NULL) < 0) {
	fprintf(stderr, "ERROR: Failed to mount /sys\n");
    }

    if (mount("devtmpfs", "/dev", "devtmpfs", 0, NULL) < 0) {
	fprintf(stderr, "ERROR: Failed to mount /dev\n");
    }

    if (mount("tmpfs", "/run", "tmpfs", 0, NULL) < 0) {
	fprintf(stderr, "ERROR: Failed to mount /run\n");
    }

    // script at /etc/init.d
    char *script[] = {"/etc/init.d/rcS", NULL};

    while (1) {
	pid_t pid = fork();
	if (pid < 0) {
	    perror("init");
	    fprintf(stderr, "ERROR: Fork failed\n");
	    sleep(2);
	    continue;
	}

	if (pid == 0) {
	    execvp(script[0], script); // execute script
	    perror("init");
	    fprintf(stderr, "ERROR: Failed to execute /etc/init.d/rcS!\n");
	} else {
	    int s;
	    waitpid(pid, &s, 0);
	}
    }
}
