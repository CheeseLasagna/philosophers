#include "philo_one.h"

size_t	ft_strlen(const char *s)
{
	size_t count;

	count = 0;
	while (s[count] != '\0')
	{
		count++;
	}
	return (count);
}

int	ft_atoi(const char *nptr)
{
	int sign;
	int number;

	sign = 1;
	number = 0;
	while ((*nptr >= 9 && *nptr <= 13) || *nptr == 32)
		nptr++;
	if (*nptr == '+' || *nptr == '-')
	{
		if (*nptr == '-')
			sign = -1;
		nptr++;
	}
	while (*nptr >= '0' && *nptr <= '9')
	{
		number = 10 * number + (*nptr - 48);
		nptr++;
	}
	number = number * sign;
	return (number);
}

int		ft_len(int n)
{
	int length;

	length = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		length++;
		n = n * -1;
	}
	while (n)
	{
		length++;
		n = n / 10;
	}
	return (length);
}

char	*ft_itoa(int n)
{
	char	*pointer;
	int		len;
	int		sign;

	sign = 1;
	len = ft_len(n);
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n < 0)
	{
		n = n * -1;
		sign = 0;
	}
	pointer = (char*)malloc(sizeof(char) * (len + 1));
	if (pointer == NULL)
		return (NULL);
	pointer[len--] = '\0';
	while (len >= 0)
	{
		pointer[len--] = n % 10 + 48;
		n = n / 10;
	}
	if (sign == 0)
		pointer[0] = '-';
	return (pointer);
}

void	ft_putstr(char *s)
{
	if (!s)
		return ;
	write(1, s, ft_strlen(s));
}

char	*ft_strdup(const char *s)
{
	char	*new;
	int		len;

	len = ft_strlen(s);
	new = (char *)malloc(sizeof(char) * (len + 1));
	if (new == NULL)
		return (NULL);
	ft_memcpy(new, s, len + 1);
	return (new);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*destination;
	unsigned char	*source;

	if (!dest && !src)
		return (NULL);
	destination = (unsigned char*)dest;
	source = (unsigned char*)src;
	while (n != 0)
	{
		*destination = *source;
		destination++;
		source++;
		n--;
	}
	return (dest);
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n < 0)
	{
		if (n == -2147483648)
		{
			write(fd, "-2147483648", 11);
			return ;
		}
		n = n * -1;
		ft_putchar_fd('-', fd);
	}
	if (n < 10)
		ft_putchar_fd(n + 48, fd);
	else
	{
		ft_putnbr_fd(n / 10, fd);
		ft_putnbr_fd(n % 10, fd);
	}
}

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
