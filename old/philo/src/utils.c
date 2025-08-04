/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmusic <mmusic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 19:49:04 by mmusic            #+#    #+#             */
/*   Updated: 2025/08/03 14:39:48 by mmusic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int ft_isnum(char c)
{
    return (c >= '0' && c <= '9');
}

int ft_strlen(char *str)
{
    int i;
    
    i = 0;
    while(*str)
    {
        i++;
        str++;
    }
    return (i);
}

long ft_atol(char *str)
{
    long out;

    out = 0;
/*     if(*str == '-')
    long sign;
    sign = 1;
    {
        sign = -1;
        str++;
    } */
    while(*str)
    {
        out = 10 * out + (*str) % '0';
        str++;
    }
    return (out);
}

time_t  current_time()
{
    struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void    ft_sleep(time_t time)
{
    time_t start;

    start = current_time();
    while(current_time() - start < time)
        usleep(200);
}

void ft_destroy(t_data *data, pthread_mutex_t *forks)
{
    int i;

    i = 0;
    pthread_mutex_destroy(&data->m_dead);
    pthread_mutex_destroy(&data->m_printing);
    while(i < data->philos[0].num_of_philos)
    {
        pthread_mutex_destroy(&forks[i]);
        pthread_mutex_destroy(data->philos[i].m_eating);
        //free(data->philos[i].m_eating);
        i++;
    }
    exit(0);
}

void    print_status(t_philo *philo, char *status)
{
    pthread_mutex_lock(philo->m_printing);
    printf("%ld %d %s\n", current_time() - philo->data->start_time, philo->id + 1, status);
    pthread_mutex_unlock(philo->m_printing);
}