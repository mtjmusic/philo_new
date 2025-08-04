/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmusic <mmusic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 18:46:13 by mmusic            #+#    #+#             */
/*   Updated: 2025/08/04 21:59:57 by mmusic           ###   ########.fr       */
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

typedef enum e_state
{
	p_eating,
	p_sleeping,
	p_thinking
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
	pthread_mutex_t		m_eating_store;
	pthread_mutex_t		*r_fork;
	pthread_mutex_t		*l_fork;
	pthread_mutex_t		*m_printing;
	pthread_mutex_t		*m_eating;
	pthread_mutex_t		*m_dead;
	t_data				*data;
	pthread_t			thread;
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

// Input
int						check_args(char **argv);
int						ft_isnum(char c);
long					ft_atol(char *str);

// Init
void					init_data_and_forks(t_data *data, t_philo *philos,
							pthread_mutex_t *forks, int philo_count);
void					init_p(t_data *data, t_philo *philos,
							pthread_mutex_t *forks, char **argv);
void					init_threads(t_data *data, t_philo *philos,
							pthread_mutex_t *forks);

// Simulation Control
bool					simulation_ended(t_data *data);
bool					set_simulation_ended(t_data *data);
bool					should_exit_or_dead(t_philo *philo);

// Philo Action
bool					eating(t_philo *philo);
void					sleeping(t_philo *philo);
void					thinking(t_philo *philo);

// Monitoring
void					*routine(void *arg);
void					*monitor_routine(void *arg);
int						check_if_all_eaten_max(t_philo *philos);

// Utility
time_t					current_time(void);
void					ft_sleep(time_t time);
void					print_status(t_philo *philo, char *status);

// Cleanup
void					ft_destroy(t_data *data, pthread_mutex_t *forks);

#endif