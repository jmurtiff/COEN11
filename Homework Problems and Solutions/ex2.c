#include <stdio.h>
#include <pthread.h>

void *loopThread(void *arg);

int	count = 0;

int main()
{
	int		i;
	pthread_t	thr[3];


	for (i = 0; i < 3; i++)
		pthread_create(&thr[i], NULL, loopThread,(void *) i);

	for (i = 0; i < 3; i++)
		pthread_join (thr[i], NULL); 

	printf ("Final count: %d\n", count);
}

void *loopThread (void *arg)
{
	int i, j;
	int threadNo = (int) arg;

	for (i = 0; i < 100000; i++)
	{
		count++;
	}

	printf ("Thread %d: %d\n", threadNo, count);
}