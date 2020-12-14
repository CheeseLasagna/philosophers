#ifndef PHILO_ONE
# define PHILO_ONE
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct	s_philo
{
	char *name;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int n_of_times_to_eat;
	long int seconds;
	long int microseconds;
	pthread_t thread;
}				t_philo;

struct timeval timestamp;
size_t	ft_strlen(const char *s);
int	ft_atoi(const char *nptr);
char	*ft_itoa(int n);
void	ft_putstr(char *s);
void	*ft_memcpy(void *dest, const void *src, size_t n);
char	*ft_strdup(const char *s);
void	ft_putnbr_fd(int n, int fd);
void	ft_putchar_fd(char c, int fd);
#endif
