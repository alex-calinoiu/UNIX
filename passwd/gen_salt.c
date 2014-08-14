#include "passwd.h"

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
        fprintf (stderr,"Can't gather entropy. Exiting!\n");
        exit (-1);
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
