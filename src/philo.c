#include "philo.h"

int	is_numeric(char *str)
{
	int i = 0;
	if (str[i] == '-' || str[i] == '+') // Допускаємо знак на початку
		i++;
	while (str[i])
	{
		if (!isdigit(str[i]))
			return (0); // Не числовий символ
		i++;
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_data			data;
	int				i;

	if (argc < 5 || argc > 6)
		ft_exit(ERR_WRONG_INPUT, NULL);
	for (int j = 1; j < argc; j++)
	{
		if (!is_numeric(argv[j]))
			ft_exit(ERR_WRONG_INPUT, NULL);
	}
	ft_initialize(argv, &data);
	i = -1;
	while (++i < data.rules.philos_total)
		pthread_join(data.philos[i].thread, NULL);
	while (--i >= 0)
		pthread_mutex_destroy(&data.forks[i].mutex);
	pthread_mutex_destroy(&data.common.state_change);
}
