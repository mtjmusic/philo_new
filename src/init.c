/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmusic <mmusic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 10:15:20 by matej             #+#    #+#             */
/*   Updated: 2025/08/04 21:53:18 by mmusic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_data_and_forks(t_data *data, t_philo *philos,
		pthread_mutex_t *forks, int philo_count)
{
	int	i;

	i = 0;
	while (i < philo_count)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
	data->philos = philos;
	pthread_mutex_init(&data->m_dead, NULL);
	pthread_mutex_init(&data->m_eating, NULL);
	pthread_mutex_init(&data->m_printing, NULL);
	data->should_exit = false;
	data->forks = forks;
}

void	init_p_state(t_philo *philo)
{
	int		i;
	bool	is_odd;

	i = 0;
	is_odd = philo->num_of_philos % 2;
	while (i < philo->num_of_philos)
	{
		if (is_odd)
		{
			if (i == philo->num_of_philos - 1)
				philo[i].state = p_thinking;
			else if (i % 2 == 0)
				philo[i].state = p_sleeping;
			else
				philo[i].state = p_eating;
		}
		else
		{
			if (i % 2 == 0)
				philo[i].state = p_thinking;
			else
				philo[i].state = p_eating;
		}
		i++;
	}
}

void	init_p_forks(int i, t_philo *philo, pthread_mutex_t *forks, char **argv)
{
	if (argv[5])
		philo->max_meals = ft_atol(argv[5]);
	else
		philo->max_meals = INT_MAX;
	if (i == 0)
	{
		philo->l_fork = &forks[ft_atol(argv[1]) - 1];
		philo->r_fork = &forks[i];
	}
	else
	{
		philo->l_fork = &forks[i - 1];
		philo->r_fork = &forks[i];
	}
}

void	init_p(t_data *data, t_philo *philos, pthread_mutex_t *forks,
		char **argv)
{
	int	i;

	i = 0;
	while (i < ft_atol(argv[1]))
	{
		philos[i].id = i;
		philos[i].is_dead = false;
		philos[i].num_of_eaten_meals = 0;
		philos[i].num_of_philos = ft_atol(argv[1]);
		philos[i].start_time = data->start_time;
		philos[i].last_meal = data->start_time;
		philos[i].odd = ft_atol(argv[1]) % 2;
		philos[i].time_to_die = ft_atol(argv[2]);
		philos[i].time_to_eat = ft_atol(argv[3]);
		philos[i].time_to_sleep = ft_atol(argv[4]);
		philos[i].m_printing = &data->m_printing;
		philos[i].m_eating = &data->m_eating;
		philos[i].m_dead = &data->m_dead;
		philos[i].data = data;
		philos[i].m_eating = &philos[i].m_eating_store;
		pthread_mutex_init(philos[i].m_eating, NULL);
		init_p_forks(i, &philos[i], forks, argv);
		i++;
	}
	init_p_state(philos);
}

void	init_threads(t_data *data, t_philo *philos, pthread_mutex_t *forks)
{
	int	i;
	int	j;

	i = 0;
	(void)forks;
	while (i < philos[0].num_of_philos)
	{
		if (pthread_create(&philos[i].thread, NULL, &routine, &philos[i]) != 0)
		{
			printf("Process terminated init threads. i: %d\n", i);
			set_simulation_ended(data);
			i--;
			break ;
		}
		i++;
	}
	j = 0;
	while (i > j)
	{
		pthread_join(philos[j].thread, NULL);
		j++;
	}
}
