#ifndef _PW_H
#define _PW_H 1

#define _XOPEN_SOURCE
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>

#define SALT_SIZE 13
#define MAX_PASS_SIZE 50
#define HASH_SIZE 99
#define USER_SIZE 15

char *gen_salt ();
int find_user (char *user);

#endif
