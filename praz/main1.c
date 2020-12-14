#include <unistd.h>
#include <stdio.h>
#include <pthread.h>

pthread_t t1, t2;
pthread_mutex_t mutex;

int i = 0;

void *my_func(void *arg)
{
	pthread_detach(t1);
	pthread_mutex_lock(&mutex);
	while (i < 100)
	{
		printf("i = %d\n", i);
		i++;
	}
	pthread_mutex_unlock(&mutex);
	printf("thread ONE done\n");
	return (NULL);
}

void *my_func2(void *arg)
{
	pthread_detach(t2);
	pthread_mutex_lock(&mutex);
	while (i < 100)
	{
		printf("i = %d\n", i);
		i++;
	}
	pthread_mutex_unlock(&mutex);
	printf("thread TWO done\n");
	return (NULL);
}

int main()
{
	pthread_mutex_init(&mutex, NULL);
	pthread_create(&t1, NULL, my_func, NULL);
	pthread_create(&t2, NULL, my_func2, NULL);
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	//sleep(1);
	printf("PRIVET JILIBAJAM\n");
	return (0);
}
