#include <stdio.h>
#include <pthread.h>

void *loopThread(void *arg);


pthread_mutex_t	mutex;
int		count = 0;


int main()
{
	int		i;
	pthread_t	thr[3];

	pthread_mutex_init (&mutex, NULL);

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
		pthread_mutex_lock (&mutex);
		count++;
		pthread_mutex_unlock (&mutex);
	}

	printf ("Thread %d: %d\n", threadNo, count);
}