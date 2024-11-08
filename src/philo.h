#ifndef PHILO_H
# define PHILO_H

# define DEAD 0
# define ALL_FINE 1
# define EATING 2
# define SLEEPING 3
# define THINKING 4
# define HUNGRY 5
# define ATE_ENOUGH 6
# define TAKING_FORK 7

# define ERROR 8
# define ERR_WRONG_INPUT 9
# define ERR_FORKS_INIT_FAILED 10
# define ERR_PHILOS_INIT_FAILED 11
# define STOP 42

# define RESET "\033[0m"
# define RED "\033[31m"
# define GREEN "\033[32m"
# define YELLOW "\033[33m"
# define BLUE "\033[34m"
# define PINK "\033[35m"
# define STR_DEAD RED "died\n" RESET
# define STR_EATING PINK "is eating\n" RESET
# define STR_SLEEPING YELLOW "is sleeping\n" RESET
# define STR_THINKING BLUE "is thinking\n" RESET
# define STR_FORK GREEN "has taken a fork\n" RESET

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdbool.h>
# include <limits.h>
# include <ctype.h>

typedef struct s_fork
{
	pthread_mutex_t	mutex;
	bool			is_taken;
}				t_fork;

typedef struct s_rules
{
	int				philos_total;
	long			to_die;
	long			to_eat;
	long			to_sleep;
	long			start;
	int				times_must_eat;
}				t_rules;

typedef struct s_common
{
	pthread_mutex_t	state_change;
	int				philos_ate_enough;
	bool			someone_died;
}				t_common;

typedef struct s_philsopher
{
	int				id;
	int				times_ate;
	long			last_meal;
	long			next_meal_before;
	long			current;
	long			offset;
	t_fork			*left_fork;
	t_fork			*right_fork;
	t_rules			rules;
	t_common		*common;
	pthread_t		thread;
}				t_philosopher;

typedef struct s_data
{
	t_fork			forks[200];
	t_philosopher	philos[200];
	t_rules			rules;
	t_common		common;
}					t_data;


void	ft_initialize(char **argv, t_data *data);
void	*ft_process(void *arg);
int		ft_eat(t_philosopher *philo, t_fork *first_fork, t_fork *second_fork);
int		ft_state_change(t_philosopher *philo, int new_state);
void	ft_die(long current, t_philosopher *philo);
int		ft_fork_take(t_philosopher *philo, t_fork *fork);
void	ft_fork_put(t_fork *fork);
long	ft_atol(const char *str);
int		ft_wait(t_philosopher *philo, long timestamp);
void	ft_print_message(t_philosopher *philo, char *str);
long	ft_get_current(long *current);
void	ft_exit(int code, t_data *data);

#endif