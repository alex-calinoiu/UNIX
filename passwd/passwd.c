#include "passwd.h"

int main(int argc, char *argv[])
{
    char *pass, *hash, *user, tmp[2]={0}, *fields;
    int fd, i=0, bytes_left;
    off_t offset, offset2;
    pass = malloc (MAX_PASS_SIZE);
    hash = malloc (HASH_SIZE);
    user = malloc (USER_SIZE);

/*If username is not passed as an argument, use root as default.*/
    if (argc == 2)
    {
        strcpy (user,argv[1]);
    } else
    if (argc == 1)
    {
        strcpy (user,"root");
    }
    else
    {
        fprintf (stderr,"Usage: passwd <user>\nNo arguments defaults to root user\n");
        exit (-1);
    }
    if ((fd=find_user (user)) < 0)
    {
        exit (-1);
    }
    printf ("UNIX password: ");
    scanf ("%50s",pass);
    hash=crypt (pass,gen_salt());
    offset = lseek (fd,0,SEEK_CUR);
    do
    {
        read (fd,tmp,1);
    } while (tmp[0] != ':');
    offset2 = lseek (fd,0,SEEK_CUR);

/*From the current offset, calculate, allocate memory,
  and read all the bytes until EOF, then return to the previous offset*/
    bytes_left = (abs (lseek(fd,0,SEEK_CUR) - lseek (fd,0,SEEK_END)));
    fields = malloc (bytes_left+1);
    memset (fields,0,bytes_left+1);
    lseek (fd,offset2,SEEK_SET);
    read (fd,fields,bytes_left);
    strcat (fields,"\0");
    lseek (fd,offset,SEEK_SET);

/*Write the final hash value into the file*/
    if ((write (fd,hash,(HASH_SIZE-1))) != (HASH_SIZE-1))
    {
        fprintf (stderr,"Error writing password in shadow file!\n");
        exit (-1);
    }
    write (fd,":",1);

/*Write the remaining of the file after the hash was written*/
    for (;;)
    {
        tmp[0] = fields [i];
        if (tmp[0] == '\0')
        {
            break;
        }
        write (fd,tmp,1);
        i++;
    }
    printf ("Password succesfully changed!\n");
    return 0;
}

