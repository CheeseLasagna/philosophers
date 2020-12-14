#include "philo_one.h"
#include <stdio.h>

pthread_mutex_t mutex;

void free_philosophers(t_philo **philos, int number)
{
	t_philo **temp;

	if (philos == NULL)
		return ;
	temp = philos;
	while (number-- != 0)
	{
		if (*temp != NULL)
			if ((*temp)->name != NULL)
				free((*temp)->name);
			free(*temp);
		temp++;
	}
	free (philos);
}

void add_philosophers(int argc, char **argv, t_philo **philos)
{
	t_philo **temp;
	int n_of_philos;
	int	i; 

	temp = philos;
	n_of_philos = ft_atoi(argv[1]);
	i = 0;
	gettimeofday(&timestamp, NULL);
	while (i != n_of_philos)
	{
		*temp = (t_philo*)malloc(sizeof(t_philo));
		(*temp)->name = ft_itoa(++i);
		(*temp)->time_to_die = ft_atoi(argv[2]);
		(*temp)->time_to_eat = ft_atoi(argv[3]);
		(*temp)->time_to_sleep = ft_atoi(argv[4]);
		(*temp)->seconds = timestamp.tv_sec;
		(*temp)->microseconds = timestamp.tv_usec;
		if (argc == 6)
			(*temp)->n_of_times_to_eat = ft_atoi(argv[5]);
		else
			(*temp)->n_of_times_to_eat = -1;
		temp++;
	}
}
	
t_philo **check_and_fill_args(int argc, char **argv)
{
	t_philo **philos;
	if (argc > 6 || argc < 5)
	{
		ft_putstr("wrong number of arguments\n");
		return (NULL);
	}
	philos = (t_philo**)malloc(sizeof(t_philo*) * ft_atoi(argv[1]));
	add_philosophers(argc, argv, philos);
	return (philos);
}
void print_timestamp(long int sec, long int micro)
{
	int miliseconds;

	gettimeofday(&timestamp, NULL);
	sec = timestamp.tv_sec - sec;
	micro = timestamp.tv_usec - micro;
	sec = sec * 1000;
	micro = micro / 1000;
	sec = sec + micro;
	miliseconds = (int)sec;
	ft_putnbr_fd(miliseconds, 1);
	write(1, " ", 1);
}

void *funky(void *arg)
{
	t_philo *temp;

	temp = (t_philo*)arg;
	pthread_mutex_lock(&mutex);
	print_timestamp(temp->seconds, temp->microseconds);
	ft_putstr(temp->name);
	ft_putstr(" is eating\n");
	usleep((temp->time_to_eat) * 1000);
	print_timestamp(temp->seconds, temp->microseconds);
	ft_putstr(temp->name);
	ft_putstr(" is sleeping\n");
	usleep((temp->time_to_sleep) * 1000);
	print_timestamp(temp->seconds, temp->microseconds);
	ft_putstr(temp->name);
	ft_putstr(" is thinking\n");
	usleep((temp->time_to_die) * 1000);
	print_timestamp(temp->seconds, temp->microseconds);
	ft_putstr(temp->name);
	ft_putstr(" died\n\n");
	pthread_mutex_unlock(&mutex);
}

int main(int argc, char **argv)
{
	t_philo **philos;
	t_philo **temp;
	int number;

	philos = check_and_fill_args(argc, argv);
	if (philos == NULL)
		return (1);
	pthread_mutex_init(&mutex, NULL);

	temp = philos;
	number = ft_atoi(argv[1]);
	/*while (number-- != 0)
	{
		printf("name = %s\n", (*temp)->name);
		printf("time_to_die = %i\n", (*temp)->time_to_die);
		printf("time_to_eat = %i\n", (*temp)->time_to_eat);
		printf("time_to_sleep = %i\n", (*temp)->time_to_sleep);
		printf("n_of_times_to_eat = %i\n\n", (*temp)->n_of_times_to_eat);
		temp++;
	}*/
	while (number-- != 0)
	{
		pthread_create(&((*temp)->thread), NULL, funky, *temp);
		temp++;
	}
	temp = philos;
	number = ft_atoi(argv[1]);
	while (number-- != 0)
	{
		pthread_join((*temp)->thread, NULL);
		temp++;
	}
	free_philosophers(philos, ft_atoi(argv[1]));
	return (0);
}	
	
