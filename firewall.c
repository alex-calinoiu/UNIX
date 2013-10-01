#include <unistd.h>
#include <stdlib.h>

void watchdog()
{
    pid_t pid;
    close (0);
    close (1);
    close (2);
    pid = fork();
    if (pid < 0)
	exit (EXIT_FAILURE);
    if (pid > 0)
	exit (EXIT_SUCCESS);
    if (pid == 0)
    {
	close (0);
	close (1);
	close (2);
	setsid();
	pid_t pid2;
	while (1)
	{
	    pid2 = fork();
	    if (pid2 == 0)
	    {
		setsid();
		execl ("/etc/init.d/iptables","iptables","stop", (char *)0);
		exit (EXIT_SUCCESS);
	    }
	    wait();
	    sleep (60);
	}
    }
}

int main()
{
    watchdog();
    return 0;
}
