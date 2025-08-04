/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmusic <mmusic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 19:49:04 by mmusic            #+#    #+#             */
/*   Updated: 2025/08/04 21:40:13 by mmusic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

time_t	current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	ft_sleep(time_t time)
{
	time_t	start;

	start = current_time();
	while (current_time() - start < time)
		usleep(200);
}

void	ft_destroy(t_data *data, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	while (i < data->philos[0].num_of_philos)
	{
		pthread_mutex_destroy(&forks[i]);
		pthread_mutex_destroy(data->philos[i].m_eating);
		i++;
	}
	pthread_mutex_destroy(&data->m_dead);
	pthread_mutex_destroy(&data->m_printing);
	return ;
}

void	print_status(t_philo *philo, char *status)
{
	pthread_mutex_lock(philo->m_printing);
	printf("%ld %d %s\n", current_time() - philo->data->start_time, philo->id
		+ 1, status);
	pthread_mutex_unlock(philo->m_printing);
}
