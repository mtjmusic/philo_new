/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmusic <mmusic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 18:11:09 by mmusic            #+#    #+#             */
/*   Updated: 2025/08/04 21:51:48 by mmusic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	handle_single_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	print_status(philo, "has taken a fork");
	ft_sleep(philo->time_to_die + 1);
	pthread_mutex_unlock(philo->l_fork);
	return (false);
}

bool	acquire_forks(t_philo *philo)
{
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;

	if (philo->l_fork < philo->r_fork)
	{
		first_fork = philo->l_fork;
		second_fork = philo->r_fork;
	}
	else
	{
		first_fork = philo->r_fork;
		second_fork = philo->l_fork;
	}
	pthread_mutex_lock(first_fork);
	pthread_mutex_lock(second_fork);
	pthread_mutex_lock(philo->m_dead);
	if (philo->data->should_exit || philo->is_dead)
	{
		pthread_mutex_unlock(philo->m_dead);
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
		return (false);
	}
	pthread_mutex_unlock(philo->m_dead);
	return (true);
}

bool	eating(t_philo *philo)
{
	if (should_exit_or_dead(philo))
		return (false);
	if (simulation_ended(philo->data))
		return (false);
	if (philo->num_of_philos == 1)
		return (handle_single_philo(philo));
	if (!acquire_forks(philo))
		return (false);
	print_status(philo, "has taken a fork");
	print_status(philo, "has taken a fork");
	print_status(philo, "is eating");
	pthread_mutex_lock(philo->m_dead);
	philo->last_meal = current_time();
	pthread_mutex_unlock(philo->m_dead);
	ft_sleep(philo->time_to_eat);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_lock(philo->m_eating);
	philo->num_of_eaten_meals++;
	pthread_mutex_unlock(philo->m_eating);
	philo->state = p_sleeping;
	return (true);
}

void	sleeping(t_philo *philo)
{
	if (should_exit_or_dead(philo))
		return ;
	if (!simulation_ended(philo->data))
		print_status(philo, "is sleeping");
	ft_sleep(philo->time_to_sleep);
	philo->state = p_thinking;
}

void	thinking(t_philo *philo)
{
	int	t_eat;
	int	t_sleep;
	int	t_think;

	if (should_exit_or_dead(philo))
		return ;
	if (!simulation_ended(philo->data))
		print_status(philo, "is thinking");
	t_eat = philo->time_to_eat;
	t_sleep = philo->time_to_sleep;
	t_think = 1;
	if (t_eat > t_sleep)
		t_think = t_eat - t_sleep;
	ft_sleep(t_think);
	usleep(500);
}
