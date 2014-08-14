CC = gcc
CFLAGS = -Wall
LDFLAGS = -lcrypt

all: passwd

passwd: passwd.o passwd.h find_user.o gen_salt.o

passwd.o: passwd.c passwd.h

find_user.o: find_user.c passwd.h

gen_salt.o: gen_salt.c passwd.h

.PHONY: clean
clean:
	rm -f *.o passwd
