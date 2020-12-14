#include <unistd.h>
#include <stdio.h>
#include <pthread.h>

pthread_t t1;

void *my_func(void *arg)
{
//	pthread_detach(t1);
	printf("NEW THREAD\n");
	return (NULL);
}

int main()
{
	pthread_create(&t1, NULL, my_func, NULL);
	pthread_join(t1, NULL);
//	sleep(1);
	printf("PRIVET JILIBAJAM\n");
	return (0);
}
