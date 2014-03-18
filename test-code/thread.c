#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

pthread_t tid;

void * thr_fn(void *arg);

int main()
{
	pthread_create (&tid,NULL,thr_fn,NULL);
	pthread_join (tid,NULL);
	printf ("Thread exited\n");
	return 0;
}

void * thr_fn (void *arg)
{
	printf ("In thread!\n");
	printf ("%p\n",tid);
	sleep (5);
	pthread_exit((void *) 0);
}
