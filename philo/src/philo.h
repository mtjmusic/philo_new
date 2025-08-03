/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmusic <mmusic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 18:46:13 by mmusic            #+#    #+#             */
/*   Updated: 2025/08/03 14:13:23 by mmusic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

typedef struct s_data	t_data;

typedef enum s_state
{
	EATING,
	SLEEPING,
	THINKING
}						t_state;

typedef struct s_philo
{
	int					id;
	int					num_of_philos;
	bool				odd;
	time_t				last_meal;
	time_t				time_to_die;
	time_t				time_to_sleep;
	time_t				time_to_eat;
	time_t				start_time;
	int					num_of_eaten_meals;
	int					max_meals;
	bool				is_dead;
	t_state				state;
	pthread_mutex_t		*r_fork;
	pthread_mutex_t		*l_fork;
	pthread_mutex_t		*m_printing;
	pthread_mutex_t		m_eating_store;
	pthread_mutex_t		*m_eating;
	pthread_mutex_t		*m_dead;
	pthread_t			thread;
	t_data				*data;
}						t_philo;

typedef struct s_data
{
	pthread_mutex_t		m_printing;
	pthread_mutex_t		m_eating;
	pthread_mutex_t		m_dead;
	t_philo				*philos;
	pthread_mutex_t		*forks;
	time_t				start_time;
	bool				should_exit;
}						t_data;

long					ft_atol(char *str);
int						ft_isnum(char c);
void					ft_destroy(t_data *data, pthread_mutex_t *forks);
time_t					current_time(void);
void					print_status(t_philo *philo, char *status);
void					ft_sleep(time_t time);

void					init_p(t_data *data, t_philo *philos,
							pthread_mutex_t *forks, char **argv);
void					init_forks(pthread_mutex_t *forks, int philo_count);
void					init_data(t_data *data, t_philo *philos,
							pthread_mutex_t *forks);
void					init_threads(t_data *data, t_philo *philos,
							pthread_mutex_t *forks);
void					*routine(void *arg);
bool    check_dead(t_philo *philo);

void    init_monitor(pthread_t *monitor, t_philo *philos, t_data *data);
void    *monitor_routine(void *arg);

int check_if_all_eaten_max(t_philo *philos);
#endif