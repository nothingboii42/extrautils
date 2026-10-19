CC = gcc
CFLAGS = -Wall -Wextra -g -O2 -march=native -mtune=native -ftree-vectorize

DESTDIR = /

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
	halt

all: extrautils
extrautils:
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
	$(CC) $(CFLAGS) -c src/halt.c -o halt.o
	$(CC) $(CFLAGS) halt.o -o halt
	$(CC) $(CFLAGS) date.o -o date
	$(CC) $(CFLAGS) arch.o -o arch
	$(CC) $(CFLAGS) clear.o -o clear
	$(CC) $(CFLAGS) pwd.o -o pwd
	$(CC) $(CFLAGS) sleep.o -o sleep
	$(CC) $(CFLAGS) whoami.o -o whoami
	$(CC) $(CFLAGS) extrautils.o -o extrautils
	$(CC) $(CFLAGS) echo.o -o echo
	$(CC) $(CFLAGS) home.o -o home
	$(CC) $(CFLAGS) uname.o -o uname
	gzip -vk man/*.1

.PHONY: clean install
clean:
	@rm -fv *.o
	@rm -fv $(BINS)
	@rm -fv man/*.gz

install:
	@mkdir -pv $(DESTDIR)/usr/bin
	@mkdir -pv $(DESTDIR)/usr/share/man/man1
	@cp -fv $(BINS) $(DESTDIR)/usr/bin
	@cp -fv man/*.gz $(DESTDIR)/usr/share/man/man1
