/* Init system for extrautils, systemd is bloat so yeah */

// nobody views this project so idc, still gonna make it

#include <unistd.h>
#include <stdio.h>
#include <sys/mount.h>
#include <string.h>
#include <sys/reboot.h>
#include <sys/stat.h>
#include <sys/wait.h>

int poweroff(void) {
    if (reboot(RB_POWER_OFF) == -1) {
        return 1;
    }
}

int halt(void) {
    // execute reboot system call
    if (reboot(RB_HALT_SYSTEM) == -1) {
        return 1;
    }
}

int restart(void) {
    if (reboot(RB_AUTOBOOT) == -1) {
        return 1; // it failed
    }
}

int spawn_shell(const char *tty) {
    pid_t pid = fork();
    if (pid == 0) {
        setsid();
        int fd = open(tty, O_RDWR);
        if (fd >= 0) {
            ioctl(fd, TIOCSCTTY, 1);
            dup2(fd, 0); dup2(fd, 1); dup2(fd, 2);
            if (fd > 2) close(fd);
        }
        char *shell[] = { "/bin/sh", "--login", "-i", NULL };
        execv(shell[0], shell);
        _exit(1);
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
    if (geteuid()) {
        fprintf(stderr, "%s: must be running as root!\n", argv[0]);
        return 1;
    }

    // check what is the inits name
    const char *name = strrchr(argv[0], '/');
    name = (name != NULL) ? name + 1 : argv[0];

    // what is the files name
    if (strcmp(name, "reboot") == 0) {
        sync();
        if (reboot(RB_AUTOBOOT) == -1) {
            return 1; // it failed
        }
    } else if (strcmp(name, "poweroff") == 0) {
        sync();
        if (reboot(RB_POWER_OFF) == -1) {
            return 1;
        }
    } else if (strcmp(name, "halt") == 0) {
        if (reboot(RB_HALT_SYSTEM) == -1) {
            return 1;
        }
    }

    // options like reboot, poweroff, halt, --help
    if (argc > 1 && strcmp(argv[1], "reboot") == 0) {
	sync();
	int poop = restart();
	return poop;
    } else if (argc > 1 && strcmp(argv[1], "poweroff") == 0) {
	sync();
	int fucked = poweroff();
	return fucked; // hope it didnt fail
    } else if (argc > 1 && strcmp(argv[1], "halt") == 0) {
	sync();
	int shit = halt();
	return shit; // hope this also didnt fail
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

    pid_t rcs = fork();
    if (rcs == 0) {
        execv(script[0], script);
        _exit(1);
    }
    waitpid(rcs, NULL, 0);

    // use the function to spawn a shell on console
    pid_t sp = spawn_shell("/dev/console");
    while (1) {
        int status;
        pid_t dead = waitpid(-1, &status, 0);

        if (dead == sp) {
            sp = spawn_shell("/dev/console"); // respawn shell
        }
    }

    return 0;
}
