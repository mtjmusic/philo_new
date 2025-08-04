/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmusic <mmusic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 21:21:26 by mmusic            #+#    #+#             */
/*   Updated: 2025/08/04 21:51:41 by mmusic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	stop_routine(t_philo *philo)
{
	bool	should_exit;

	pthread_mutex_lock(philo->m_dead);
	should_exit = philo->data->should_exit || philo->is_dead;
	pthread_mutex_unlock(philo->m_dead);
	return (should_exit);
}

bool	continue_routine(t_philo *philo)
{
	return (!stop_routine(philo));
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (continue_routine(philo)
		&& philo->num_of_eaten_meals < philo->max_meals)
	{
		if (philo->state == p_eating)
		{
			if (continue_routine(philo) && !eating(philo))
				return (NULL);
		}
		else if (philo->state == p_sleeping && continue_routine(philo))
			sleeping(philo);
		else if (philo->state == p_thinking && continue_routine(philo))
		{
			thinking(philo);
			philo->state = p_eating;
		}
	}
	return (NULL);
}

static void	set_philo_dead(t_philo *philo)
{
	pthread_mutex_lock(philo->m_dead);
	philo->is_dead = true;
	philo->data->should_exit = true;
	pthread_mutex_unlock(philo->m_dead);
}

void	*monitor_routine(void *arg)
{
	t_philo	*philos;
	int		i;
	time_t	last_meal;

	philos = (t_philo *)arg;
	while (1)
	{
		i = 0;
		while (i < philos[0].num_of_philos)
		{
			pthread_mutex_lock(philos[i].m_dead);
			last_meal = philos[i].last_meal;
			pthread_mutex_unlock(philos[i].m_dead);
			if (current_time() - last_meal > philos[i].time_to_die)
			{
				print_status(&philos[i], "died");
				return (set_philo_dead(&philos[i]), NULL);
			}
			if (check_if_all_eaten_max(philos))
				return (NULL);
			i++;
			ft_sleep(1);
		}
	}
	return (NULL);
}
