# My first and last saturween as a kid! thats what other people are calling it...
# Happy halloween, dont eat to much candy (might be a different day rn)

CC = gcc
CFLAGS = -Wall -Wextra -g -O2 -march=native -mtune=native -ftree-vectorize -Wconversion -Wdouble-promotion -Wshadow -Wformat=2 -fstack-protector-strong -D_FORTIFY_SOURCE=2 -fstack-clash-protection -fsanitize=address

DESTDIR = /

INIT = \
	init/init \
	reboot \
	poweroff \
	halt

SHOBJ = \
	obj/sh.o \
	obj/shell.o

BINS = \
	clear \
	pwd \
	extrautils \
	sleep \
	whoami \
	echo \
	home \
	uname \
	arch \
	date \
	env \
	touch \
	sh

all: extrautils
extrautils:
	mkdir -pv obj
	$(CC) $(CFLAGS) -c src/touch.c -o touch.o
	$(CC) $(CFLAGS) -c src/clear.c -o clear.o
	$(CC) $(CFLAGS) -c src/pwd.c -o pwd.o
	$(CC) $(CFLAGS) -c src/extrautils.c -o extrautils.o
	$(CC) $(CFLAGS) -c src/sleep.c -o sleep.o
	$(CC) $(CFLAGS) -c src/whoami.c -o whoami.o
	$(CC) $(CFLAGS) -c src/echo.c -o echo.o
	$(CC) $(CFLAGS) -c src/home.c -o home.o
	$(CC) $(CFLAGS) -c src/uname.c -o uname.o
	$(CC) $(CFLAGS) -c src/arch.c -o arch.o
	$(CC) $(CFLAGS) -c src/date.c -o date.o
	$(CC) $(CFLAGS) -c init/halt.c -o halt.o
	$(CC) $(CFLAGS) -c init/poweroff.c -o poweroff.o
	$(CC) $(CFLAGS) -c init/reboot.c -o reboot.o
	$(CC) $(CFLAGS) -c src/env.c -o env.o
	mv -fv *.o obj/
	$(CC) $(CFLAGS) obj/poweroff.o -o poweroff
	$(CC) $(CFLAGS) obj/reboot.o -o reboot
	$(CC) $(CFLAGS) obj/halt.o -o halt
	$(CC) $(CFLAGS) obj/date.o -o date
	$(CC) $(CFLAGS) obj/arch.o -o arch
	$(CC) $(CFLAGS) obj/clear.o -o clear
	$(CC) $(CFLAGS) obj/pwd.o -o pwd
	$(CC) $(CFLAGS) obj/sleep.o -o sleep
	$(CC) $(CFLAGS) obj/whoami.o -o whoami
	$(CC) $(CFLAGS) obj/extrautils.o -o extrautils
	$(CC) $(CFLAGS) obj/echo.o -o echo
	$(CC) $(CFLAGS) obj/home.o -o home
	$(CC) $(CFLAGS) obj/uname.o -o uname
	gzip -vk man/*.1
	$(CC) $(CFLAGS) obj/env.o -o env
	$(CC) $(CFLAGS) obj/touch.o -o touch
	$(CC) $(CFLAGS) -c init/init.c -o init.o
	$(CC) $(CFLAGS) -c shell/sh.c -o sh.o
	$(CC) $(CFLAGS) -c shell/shell.c -o shell.o
	mv -fv *.o obj/
	$(CC) $(CFLAGS) obj/init.o -o init/init
	$(CC) $(CFLAGS) $(SHOBJ) -o sh

.PHONY: clean install
clean:
	@rm -rfv obj/
	@rm -fv *.o
	@rm -fv $(BINS)
	@rm -fv $(INIT)
	@rm -fv man/*.gz

install:
	@mkdir -pv $(DESTDIR)/usr/bin
	@mkdir -pv $(DESTDIR)/usr/share/man/man1
	@mkdir -pv $(DESTDIR)/usr/sbin
	@cp -fv $(BINS) $(DESTDIR)/usr/bin
	@cp -fv $(INIT) $(DESTDIR)/usr/sbin
	@cp -fv man/*.gz $(DESTDIR)/usr/share/man/man1
	@mkdir -pv $(DESTDIR)/etc/init.d
	@cp -fv init/rcS $(DESTDIR)/etc/init.d
	@cd $(DESTDIR) && ln -sv usr/bin bin
	@cd $(DESTDIR) && ln -sv usr/sbin sbin
	@chmod -v +x $(DESTDIR)/etc/init.d/*
