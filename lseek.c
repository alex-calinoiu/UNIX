#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
	off_t pos;
	int fd;
	fd = open (argv[1],O_RDWR);
	if ( fd == -1 )
	{
		printf ("Error opening file!\n");
		exit (EXIT_FAILURE);
	}
	pos = lseek (fd,0,SEEK_END);
	printf ("Size: %ld\n",pos);
	return 0;
}
