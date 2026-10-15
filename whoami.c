#include <stdio.h>
#include <unistd.h>
#include <pwd.h>

int main(void) {
    uid_t id = geteuid();
    struct passwd *pwd = getpwuid(id);

    if (pwd) {
	puts(pwd->pw_name);
    }

    return 0;
}
