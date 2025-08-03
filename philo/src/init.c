/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmusic <mmusic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 10:15:20 by matej             #+#    #+#             */
/*   Updated: 2025/08/03 14:33:50 by mmusic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void init_data(t_data *data, t_philo *philos, pthread_mutex_t *forks)
{
    data->philos = philos;   
    pthread_mutex_init(&data->m_dead, NULL);
    //pthread_mutex_init(&data->m_eating, NULL);
    pthread_mutex_init(&data->m_printing, NULL);
    data->should_exit = false;
    data->forks = forks;
}

void init_forks(pthread_mutex_t *forks, int philo_count)
{
    int i;

    i = 0;
    while(i < philo_count)
    {
        pthread_mutex_init(&forks[i], NULL);
        i++;
    }
}

void    init_p_state(t_philo *philo)
{
    int i;
    bool is_odd;

    i = 0;
    is_odd = philo->num_of_philos % 2;
    while(i < philo->num_of_philos)
    {
        if(is_odd)
        {
            if(i == philo->num_of_philos - 1)
                philo[i].state = THINKING;
            else if(i % 2 == 0)
                philo[i].state = SLEEPING;
            else
                philo[i].state = EATING;
        }
        else
        {
            if(i % 2 == 0)
                philo[i].state = THINKING;
            else
                philo[i].state = EATING;
        }
        /* if(philo[i].state == EATING)
            printf("philo %d state EATING\n", philo[i].id + 1);
        else if(philo[i].state == SLEEPING)
            printf("philo %d state SLEEPING\n", philo[i].id + 1);
        else if(philo[i].state == THINKING)
            printf("philo %d state THINKING\n", philo[i].id + 1); */
        i++;
    }
}

void    init_p(t_data *data, t_philo *philos, pthread_mutex_t *forks, char **argv)
{
    int i;

    i = 0;
    while(i < ft_atol(argv[1]))
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
        if(argv[5])
            philos[i].max_meals = ft_atol(argv[5]);
        else
            philos[i].max_meals = INT_MAX;
        philos[i].m_printing = &data->m_printing;
        //philos[i].m_eating = &data->m_eating;
        philos[i].m_dead = &data->m_dead;
        philos[i].data = data;
        //philos[i].m_eating = malloc(sizeof(pthread_mutex_t));
        philos[i].m_eating = &philos[i].m_eating_store;
        pthread_mutex_init(philos[i].m_eating, NULL);
        if(i == 0)
        {
            philos[i].l_fork = &forks[ft_atol(argv[1]) - 1];
            philos[i].r_fork = &forks[i];
        }
        else
        {
            philos[i].l_fork = &forks[i - 1];
            philos[i].r_fork = &forks[i];
        }
        i++;
    }
    init_p_state(philos);    
}

void    init_threads(t_data *data, t_philo *philos, pthread_mutex_t *forks)
{
    int i;

    i = 0;
    while(i < philos[0].num_of_philos)
    {
        if(pthread_create(&philos[i].thread, NULL, &routine, &philos[i]) != 0)
            ft_destroy(data, forks);
        i++;
    }
    i = 0;
    while(i < philos[0].num_of_philos)
    {
        if(pthread_join(philos[i].thread, NULL) != 0)
            ft_destroy(data, forks);
        i++;
    }
}

void    init_monitor(pthread_t *monitor, t_philo *philos, t_data *data)
{
    if(pthread_create(monitor, NULL, &monitor_routine, (void*)philos) != 0)
        ft_destroy(data, data->forks);
    if(pthread_join(*monitor, NULL) != 0)
        ft_destroy(data, data->forks);
}