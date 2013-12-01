#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char *argv[])
{
	DIR * p1;
	struct dirent * p2;
	char *x;
	int fd;
	if (argc != 2)
	{
		fprintf (stderr,"Not enough arguments!\n");
		exit (EXIT_FAILURE);
	}
	if ((p1=opendir(argv[1])) == NULL)
	{
		fprintf (stderr,"Error opening folder!\n");
		exit (EXIT_FAILURE);
	}
	x=malloc(1024);
	while ((p2=readdir(p1)) != NULL)
	{
	    	strcpy (x,argv[1]);
	    	strcat (x,"/");
		strcat (x,p2->d_name);
		if (((opendir(x)) == NULL) && (p2->d_name[0] != '.'))
		{
			printf ("File: %s\t",p2->d_name);
			if ((fd = (open (x,O_RDONLY))) == -1)
			{
				fprintf (stderr,"Error opening file!\n");
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
	return 0;
}
