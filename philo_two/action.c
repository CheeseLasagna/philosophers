#include "philo_two.h"

void	philo_take_forks(t_philo *philo)
{
	sem_wait(philo->general_info->fork_sem);
	philo->action_time = get_time();
	philo_status_print(philo, TOOK_FORK);
	sem_wait(philo->general_info->fork_sem);
	philo->action_time = get_time();
	philo_status_print(philo, TOOK_FORK);
}

void	philo_eat(t_philo *philo)
{
	philo->next_death_time = get_time() + philo->general_info->time_to_die;
	philo->action_time = get_time();
	philo_status_print(philo, EATING);
	usleep(philo->general_info->time_to_eat * 1000);
	(philo->finished_meals)++;
	sem_post(philo->general_info->fork_sem);
	sem_post(philo->general_info->fork_sem);
}

void	philo_sleep(t_philo *philo)
{
	philo->action_time = get_time();
	philo_status_print(philo, SLEEPING);
	usleep(philo->general_info->time_to_sleep * 1000);
}
