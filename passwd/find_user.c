#include "passwd.h"

/*Function to see if the user exists on the system*/
int find_user (char *user)
{
    char *tmp_user;
    int fd,us_len,i;

    tmp_user = malloc (USER_SIZE);
    us_len = strlen(user);

/*Exit if there is an error opening the shadow file*/
    if ((fd = open("/etc/shadow",O_RDWR)) < 0)
    {
        fprintf (stderr,"Unable to open shadow file... Exiting!\n");
        exit (-1);
    }

/*Read the first strlen(user) bytes from the beginning of the line*/
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
