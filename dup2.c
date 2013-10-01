#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int fd1,fd2,temp_fd,j=0,vec_fd[100],i;
    if (argc != 3)
    {
	printf ("Argument error!\n");
	exit (-1);
    }
    fd1=atoi(argv[1]);
    fd2=atoi(argv[2]);
    if ((temp_fd = dup(fd1)) == -1)
    {
	printf ("First fd doesn't exist!\n");
	exit (-1);
    }
    if (fd1 == fd2)
    {
	printf ("FDs equal\n");
	exit (0);
    }
    close (temp_fd);
    if (fd2 > fd1)
    {
	close (fd2);
	for (i=fd1;i<fd2;i++)
	{
	    if ((temp_fd = dup(fd1)) != -1)
	    {
		vec_fd[j] = temp_fd;
		j++;
	    }
	}
    }
    if (fd2 < fd1)
    {
	close (fd2);
	for (i=0;i<=fd2;i++)
	{
	    if ((temp_fd = dup(fd1)) != -1)
	    {
		vec_fd[j]=temp_fd;
		j++;
	    }
	}
    }
    for (i=0;i<=j;i++)
    {
	if (vec_fd[i] != fd2)
	    close (vec_fd[i]);
    }
    return 0;
}
