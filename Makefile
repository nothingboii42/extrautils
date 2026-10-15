CC = gcc
CFLAGS = -Wall -Wextra -g

BINS = \
	clear \
	pwd \
	extrautils \
	sleep \
	whoami \
	echo \
	home \
	uname

all: extrautils
extrautils:
	$(CC) $(CFLAGS) -c clear.c -o clear.o
	$(CC) $(CFLAGS) -c pwd.c -o pwd.o
	$(CC) $(CFLAGS) -c extrautils.c -o extrautils.o
	$(CC) $(CFLAGS) -c sleep.c -o sleep.o
	$(CC) $(CFLAGS) -c whoami.c -o whoami.o
	$(CC) $(CFLAGS) -c echo.c -o echo.o
	$(CC) $(CFLAGS) -c home.c -o home.o
	$(CC) $(CFLAGS) -c uname.c -o uname.o
	$(CC) $(CFLAGS) clear.o -o clear
	$(CC) $(CFLAGS) pwd.o -o pwd
	$(CC) $(CFLAGS) sleep.o -o sleep
	$(CC) $(CFLAGS) whoami.o -o whoami
	$(CC) $(CFLAGS) extrautils.o -o extrautils
	$(CC) $(CFLAGS) echo.o -o echo
	$(CC) $(CFLAGS) home.o -o home
	$(CC) $(CFLAGS) uname.o -o uname

.PHONY: clean install
clean:
	@rm -fv *.o
	@rm -fv $(BINS)

install:
	@mkdir -pv $(DESTDIR)/usr/bin
	@cp -fv $(BINS) $(DESTDIR)/usr/bin
