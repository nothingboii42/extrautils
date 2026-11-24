CC = gcc
CFLAGS = -Wall -Wextra -g -O2 -march=native -mtune=native -ftree-vectorize -Wconversion -Wdouble-promotion -Wshadow -Wformat=2 -fstack-protector-strong -D_FORTIFY_SOURCE=2 -fstack-clash-protection -fsanitize=address

DESTDIR = /

INIT = \
	init/init

SHOBJ = \
	obj/sh.o \
	obj/shell.o

BINS = \
	clear \
	pwd \
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

all: $(BINS)
$(BINS):
	mkdir -pv obj
	$(CC) $(CFLAGS) -c src/touch.c -o touch.o
	$(CC) $(CFLAGS) -c src/clear.c -o clear.o
	$(CC) $(CFLAGS) -c src/pwd.c -o pwd.o
	$(CC) $(CFLAGS) -c src/sleep.c -o sleep.o
	$(CC) $(CFLAGS) -c src/whoami.c -o whoami.o
	$(CC) $(CFLAGS) -c src/echo.c -o echo.o
	$(CC) $(CFLAGS) -c src/home.c -o home.o
	$(CC) $(CFLAGS) -c src/uname.c -o uname.o
	$(CC) $(CFLAGS) -c src/arch.c -o arch.o
	$(CC) $(CFLAGS) -c src/date.c -o date.o
	$(CC) $(CFLAGS) -c src/env.c -o env.o
	mv -fv *.o obj/
	$(CC) $(CFLAGS) obj/date.o -o date
	$(CC) $(CFLAGS) obj/arch.o -o arch
	$(CC) $(CFLAGS) obj/clear.o -o clear
	$(CC) $(CFLAGS) obj/pwd.o -o pwd
	$(CC) $(CFLAGS) obj/sleep.o -o sleep
	$(CC) $(CFLAGS) obj/whoami.o -o whoami
	$(CC) $(CFLAGS) obj/echo.o -o echo
	$(CC) $(CFLAGS) obj/home.o -o home
	$(CC) $(CFLAGS) obj/uname.o -o uname
	gzip -vkf man/*.1
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
	@rm -fv $(BINS) $(INIT)
	@rm -fv man/*.gz

install:
	mkdir -p $(DESTDIR)/usr/bin
	mkdir -p $(DESTDIR)/usr/share/man/man1
	mkdir -p $(DESTDIR)/usr/sbin
	install -p -m 755 $(BINS) $(DESTDIR)/usr/bin
	install -p -m 755 $(INIT) $(DESTDIR)/usr/sbin
	install -p -m 755 man/*.gz $(DESTDIR)/usr/share/man/man1
	mkdir -pv $(DESTDIR)/etc/init.d
	install -p -m 755 init/rcS $(DESTDIR)/etc/init.d
	cd $(DESTDIR) && ln -sf usr/bin bin
	cd $(DESTDIR) && ln -sf usr/sbin sbin
	ln -sf $(DESTDIR)/sbin/init $(DESTDIR)/sbin/reboot
	ln -sf $(DESTDIR)/sbin/init $(DESTDIR)/sbin/poweroff
	ln -sf $(DESTDIR)/sbin/init $(DESTDIR)/sbin/halt
