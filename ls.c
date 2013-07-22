#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

int main(int argc, char *argv[])
{
	DIR * p1, *tmp;
	struct dirent * p2;
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
		if ((tmp=opendir(p2->d_name)) == NULL)
		{
			printf ("File: %s\n",p2->d_name);
		}
		else
		{
			printf ("Folder: %s\n",p2->d_name);
		}
	}
	closedir (p1);
	closedir (tmp);
	return 0;
}
