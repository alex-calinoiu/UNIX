#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
	DIR * p1, *tmp;
	struct dirent * p2;
	int fd;
	if (argc != 2)
	{
		printf ("Not enough arguments!\n");
		exit (EXIT_FAILURE);
	}
	if ((p1=opendir(argv[1])) == NULL)
	{
		printf ("Error opening folder!\n");
		exit (EXIT_FAILURE);
	}
	while ((p2=readdir(p1)) != NULL)
	{
		if (((tmp=opendir(p2->d_name)) == NULL) && (p2->d_name[0] != '.'))
		{
			printf ("File: %s\t",p2->d_name);
			if ((fd = (open (p2->d_name,O_RDONLY))) == -1)
			{
				printf ("Error opening file!\n");
			} else
			{
				printf ("Size: %ld\n", lseek(fd, 0, SEEK_END));
			}
		}
		else
		if ((p2 -> d_name[0]) != '.')
		{
			printf ("Folder: %s\n",p2->d_name);
		}
	}
	closedir (p1);
	closedir (tmp);
	close (fd);
	return 0;
}
