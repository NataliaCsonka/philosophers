
#include "philo.h"

int	ft_wait(t_philosopher *philo, long timestamp)
{
	while (ft_get_current(&philo->current) < timestamp)
	{
		if (philo->current >= philo->next_meal_before)
			return (DEAD);
		usleep(philo->rules.philos_total * 10);
	}
	return (ALL_FINE);
}

void	ft_print_message(t_philosopher *philo, char *str)
{
	printf ("%ld %d %s", (ft_get_current(&philo->current)
			- philo->rules.start) / 1000, philo->id, str);
}

long	ft_get_current(long *current)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	*current = t.tv_sec * 1000000 + t.tv_usec;
	return (*current);
}

void	ft_exit(int code, t_data *data)
{
	int	i;

	if (code == ERR_WRONG_INPUT)
		printf ("Wrong input!\n");
	else if (code == ERR_FORKS_INIT_FAILED)
		printf ("Error, forks initialization failed!\n");
	else if (code == ERR_PHILOS_INIT_FAILED)
		printf ("Error, philosophers initialization failed!\n");
	if (data)
	{
		i = data->rules.philos_total;
		while (--i >= 0)
			pthread_mutex_destroy(&data->forks[i].mutex);
	}
	exit (code);
}
