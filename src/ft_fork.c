#include "philo.h"

int	ft_fork_take(t_philosopher *philo, t_fork *fork)
{
	while (ft_get_current(&philo->current) < philo->next_meal_before)
	{
		pthread_mutex_lock(&fork->mutex);
		if (fork->is_taken == true)
		{
			pthread_mutex_unlock(&fork->mutex);
			usleep(100);
		}
		else
		{
			fork->is_taken = true;
			pthread_mutex_unlock(&fork->mutex);
			if (ft_state_change(philo, TAKING_FORK) != STOP)
				return (ALL_FINE);
			else
				return (STOP);
		}
	}
	return (ft_die(philo->current, philo), DEAD);
}

void	ft_fork_put(t_fork *fork)
{
	pthread_mutex_lock(&fork->mutex);
	fork->is_taken = false;
	pthread_mutex_unlock(&fork->mutex);
}
