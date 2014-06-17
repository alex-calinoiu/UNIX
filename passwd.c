#define _XOPEN_SOURCE
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>

#define SALT_SIZE 13
#define MAX_PASS_SIZE 50
#define HASH_SIZE 99
#define USER_SIZE 15

char *gen_salt();
int find_user(char *user);

int main(int argc, char *argv[])
{
    char *pass, *hash, *user;
    int fd;
    pass = malloc (MAX_PASS_SIZE);
    hash = malloc (HASH_SIZE);
    user = malloc (USER_SIZE);

/*If username is not passed as an argument, use root as default.*/
    if (argc == 2)
    {
        strcpy (user,argv[1]);
    } else
    {
        strcpy (user,"root");
    }
    if ((fd=find_user (user)) < 0)
    {
        exit (1);
    }
    scanf ("%50s",pass);
    hash=crypt (pass,gen_salt());
    if ((write (fd,hash,(HASH_SIZE-1))) != (HASH_SIZE-1))
    {
        fprintf (stderr,"Error writing password in shadow file!\n");
        exit (-1);
    }
    printf ("Password succesfully changed!\n");
    return 0;
}

/*Function to generate random key value
 Entropy is gathered from /dev/urandom,
 and the function returns the generated salt.*/
char *gen_salt()
{
    int fd,i=0;
    char x[2] = {0},*y;
    y=malloc (SALT_SIZE);
    memset (y,0,SALT_SIZE);
    strcat (y,"$6$");
    if ((fd = open ("/dev/urandom",O_RDONLY)) < 0)
    {
        fprintf (stderr,"Can't gather entropy. Terminating!\n");
        raise (SIGKILL);
    }
/*Read one byte at a time until 8 bytes
  from the [a-zA-Z./] interval are read.*/
    for (;;)
    {
        read (fd,x,1);
        if ((x[0] < 65 || x[0] > 90) && (x[0] < 97 || x[0] > 122) && (x[0] < 48 || x[0] > 57) && x[0] != 46 && x[0] != 47)
        {
            continue;
        } else
        {
            strcat (y,x);
            i++;
        }
        if ( i == 8 )
        {
            close (fd);
            break;
        }
    }
    strcat (y,"$");
    return y;
}

/*Function to see if the suer exists on the system*/
int find_user (char *user)
{
    char *tmp_user;
    int fd,us_len,i;

    tmp_user = malloc (USER_SIZE);
    us_len = strlen(user);

/*Kill the process if there is an error opening the shadow file*/
    if ((fd = open("/etc/shadow",O_RDWR)) < 0)
    {
        fprintf (stderr,"Unable to open shadow file... Terminating!\n");
        raise (SIGKILL);
    }
    for (;;)
    {
        if ((read(fd,tmp_user,us_len)) != us_len)
        {
            close (fd);
            free (tmp_user);
            break;
        }

/*The user is not present at the current line, so jump to the next one.*/
        for (i=0;i<us_len;i++)
        {
            if (tmp_user[i] != user[i])
            {
                goto no_user;
            }
        }

/*If the user if found, the file-descriptor to the shadow file is returned.*/
        lseek (fd,1,SEEK_CUR);
        free (tmp_user);
        return fd;
no_user:

/*Read one character at a time until newline,
  in order to get to the next line.*/
        while ((tmp_user[0] != '\n'))
        {
            read(fd,tmp_user,1);
        }
    }
    fprintf (stderr,"User not found!\n");
    return -1;
}
