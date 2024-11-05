
#include "philo.h"

void	ft_initialize_philos(t_data *data)
{
	int	i;
	int	total;

	i = data->rules.philos_total;
	total = data->rules.philos_total;
	ft_get_current(&data->rules.start);
	while (--i >= 0)
	{
		data->philos[i].id = i + 1;
		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].right_fork = &data->forks[(i + 1) % total];
		data->philos[i].times_ate = 0;
		data->philos[i].rules = data->rules;
		data->philos[i].common = &data->common;
		data->philos[i].last_meal = data->rules.start;
		data->philos[i].offset = (data->rules.philos_total - i + 1) * 10;
		data->philos[i].next_meal_before = data->rules.start
			+ data->rules.to_die;
		if (pthread_create (&data->philos[i].thread, NULL,
				ft_process, (void *)&data->philos[i]))
			ft_exit(ERR_PHILOS_INIT_FAILED, data);
	}
}

void	ft_initialize_forks(t_data *data)
{
	int	i;

	i = data->rules.philos_total;
	while (--i >= 0)
	{
		data->forks[i].is_taken = false;
		if (pthread_mutex_init(&data->forks[i].mutex, NULL))
			ft_exit(ERR_FORKS_INIT_FAILED, NULL);
	}
}

void	ft_initialize_rules(char **argv, t_data *data)
{
	data->rules.philos_total = ft_atol(argv[1]);
	data->rules.to_die = ft_atol(argv[2]) * 1000;
	data->rules.to_eat = ft_atol(argv[3]) * 1000;
	data->rules.to_sleep = ft_atol(argv[4]) * 1000;
	data->rules.times_must_eat = (int)ft_atol(argv[5]);
	if (data->rules.philos_total < 1 || data->rules.philos_total > 200
		|| data->rules.to_die < 0
		|| data->rules.to_eat < 0
		|| data->rules.to_sleep < 0)
		ft_exit(ERR_WRONG_INPUT, NULL);
	data->common.philos_ate_enough = 0;
	data->common.someone_died = false;
	if (pthread_mutex_init(&data->common.state_change, NULL))
		ft_exit(ERROR, NULL);
}

void	ft_initialize(char **argv, t_data *data)
{
	ft_initialize_rules(argv, data);
	ft_initialize_forks(data);
	ft_initialize_philos(data);
}
