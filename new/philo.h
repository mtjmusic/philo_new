#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <time.h>
# include <unistd.h>

typedef enum e_state
{
	THINKING,
	EATING,
	SLEEPING,
	DEAD
}	t_state;

typedef struct s_philo
{
	int				id;
	long			last_meal_time;
	int				meals_eaten;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	int				*is_dead;
	pthread_t		thread;
	t_state			state;
}					t_philo;

typedef struct s_data
{
	int				num_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_times_each_philo_must_eat;
	long			start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*m_printing;
	t_philo			*philos;
}					t_data;

int					check_nums(char **argv);
int					check_args(char **argv);
int					ft_isnum(char c);
int					ft_strlen(char *str);
long				ft_atol(char *str);
void				ft_sleep(time_t time);

#endif
