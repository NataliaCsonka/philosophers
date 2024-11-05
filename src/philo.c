#include "philo.h"

int	main(int argc, char **argv)
{
	t_data			data;
	int				i;

	if (argc < 5 || argc > 6)
		ft_exit(ERR_WRONG_INPUT, NULL);
	ft_initialize(argv, &data);
	i = -1;
	while (++i < data.rules.philos_total)
		pthread_join(data.philos[i].thread, NULL);
	while (--i >= 0)
		pthread_mutex_destroy(&data.forks[i].mutex);
	pthread_mutex_destroy(&data.common.state_change);
}
