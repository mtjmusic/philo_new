/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_helpers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmusic <mmusic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 21:25:46 by mmusic            #+#    #+#             */
/*   Updated: 2025/08/04 21:43:00 by mmusic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_if_all_eaten_max(t_philo *philos)
{
	int	i;
	int	max;
	int	philo_count;

	i = 0;
	philo_count = philos[0].num_of_philos;
	max = philos[0].max_meals;
	while (i < philo_count)
	{
		pthread_mutex_lock(philos[i].m_eating);
		if (philos[i].num_of_eaten_meals < max)
		{
			pthread_mutex_unlock(philos[i].m_eating);
			return (0);
		}
		pthread_mutex_unlock(philos[i].m_eating);
		i++;
	}
	return (1);
}

int	min_times_eaten(t_philo *philos)
{
	int	min;
	int	i;

	i = 0;
	min = philos[0].num_of_eaten_meals;
	while (i < philos[0].num_of_philos)
	{
		if (philos[i].num_of_eaten_meals < min)
			min = philos[i].num_of_eaten_meals;
		i++;
	}
	return (min);
}

bool	should_exit_or_dead(t_philo *philo)
{
	bool	exit;

	pthread_mutex_lock(philo->m_dead);
	exit = philo->data->should_exit || philo->is_dead;
	pthread_mutex_unlock(philo->m_dead);
	return (exit);
}

bool	simulation_ended(t_data *data)
{
	bool	exit;

	pthread_mutex_lock(&data->m_dead);
	exit = data->should_exit;
	pthread_mutex_unlock(&data->m_dead);
	return (exit);
}

bool	set_simulation_ended(t_data *data)
{
	pthread_mutex_lock(&data->m_dead);
	data->should_exit = true;
	pthread_mutex_unlock(&data->m_dead);
	return (true);
}
