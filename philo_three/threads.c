#include "philo_three.h"

void	*all_philos_finished(void *arg)
{
	t_info	*info;
	int		i;

	info = (t_info*)arg;
	i = 0;
	while (i < info->philos_number)
	{
		sem_wait(info->finished_meals);
		i++;
	}
	sem_wait(info->output_sem);
	ft_putstr("All philosophers ate at least ");
	ft_putnbr(info->meals_to_eat);
	ft_putstr(" times. Exit program\n");
	sem_post(info->main_sem);
	return (NULL);
}

void	*monitor_health(void *arg)
{
	t_philo *philo;

	philo = (t_philo*)arg;
	while (1)
	{
		philo->death_time = get_time();
		if (philo->death_time > philo->next_death_time)
		{
			philo_status_print(philo, DEAD);
			sem_post(philo->general_info->main_sem);
			return (NULL);
		}
	}
	return (NULL);
}

int		philo_main(t_philo *philo)
{
	pthread_t	thread;

	philo->next_death_time = get_time() + philo->general_info->time_to_die;
	if (pthread_create(&thread, NULL, &monitor_health, philo) != 0)
		return (1);
	if (pthread_detach(thread) != 0)
		return (1);
	while (1)
	{
		philo_take_forks(philo);
		philo_eat(philo);
		philo_sleep(philo);
		philo->action_time = get_time();
		philo_status_print(philo, THINKING);
	}
	return (0);
}

int		create_philos_threads(t_info *info)
{
	int			i;
	int			exit_status;
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
		info->philo[i].pid = fork();
		if (info->philo[i].pid == 0)
		{
			exit_status = philo_main(&(info->philo[i]));
			exit(exit_status);
		}
		usleep(500);
		i++;
	}
	return (0);
}

int		create_procs_and_threads(t_info *info)
{
	info->start_time = get_time();
	if (create_philos_threads(info) != 0)
		return (THREAD_ERROR);
	return (0);
}
