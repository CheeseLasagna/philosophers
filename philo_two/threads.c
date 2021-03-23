#include "philo_two.h"

void	*all_philos_finished(void *arg)
{
	t_info	*info;
	int		i;

	info = (t_info*)arg;
	i = 0;
	while (i < info->philos_number)
	{
		sem_wait(info->hungry_philos);
		i++;
	}
	sem_wait(info->output_sem);
	printf("All philosophers ate at least %d times\n", info->meals_to_eat);
	sem_post(info->main_sem);
	return (NULL);
}

void	*monitor_health(void *arg)
{
	t_philo *philo;

	philo = (t_philo*)arg;
	while (1)
	{
		sem_wait(philo->dead);
		philo->death_time = get_time();
		if (philo->death_time > philo->next_death_time)
		{
			sem_wait(philo->general_info->output_sem);
			philo->death_time = philo->death_time -
					philo->general_info->start_time;
			printf("%ld %d is dead\n", philo->death_time, philo->name);
			sem_post(philo->general_info->main_sem);
			return (NULL);
		}
		sem_post(philo->dead);
		usleep(3000);
	}
	return (NULL);
}

void	*philo_main(void *arg)
{
	t_philo		*philo;
	pthread_t	thread;

	philo = (t_philo*)arg;
	philo->next_death_time = get_time() + philo->general_info->time_to_die;
	if (pthread_create(&thread, NULL, &monitor_health, philo) != 0)
		return (NULL);
	if (pthread_detach(thread) != 0)
		return (NULL);
	while (1)
	{
		philo_take_forks(philo);
		philo_eat(philo);
		philo_sleep(philo);
		sem_wait(philo->general_info->output_sem);
		philo->action_time = get_time() - philo->general_info->start_time;
		print_output(philo, "is thinking");
		sem_post(philo->general_info->output_sem);
	}
	return (NULL);
}

int		create_philos_threads(t_info *info)
{
	int			i;
	pthread_t	thread;

	if (info->meals_to_eat != -1)
	{
		if (pthread_create(&thread, NULL, &all_philos_finished, info) != 0)
			return (THREAD_ERROR);
		if (pthread_detach(thread) != 0)
			return (THREAD_ERROR);
	}
	i = 0;
	while (i < info->philos_number)
	{
		if (pthread_create(&thread, NULL, &philo_main, &(info->philo[i])) != 0)
			return (THREAD_ERROR);
		if (pthread_detach(thread) != 0)
			return (THREAD_ERROR);
		i++;
	}
	return (0);
}

int		create_threads(t_info *info)
{
	info->start_time = get_time();
	if (create_philos_threads(info) != 0)
		return (THREAD_ERROR);
	return (0);
}
