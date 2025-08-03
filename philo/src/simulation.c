/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmusic <mmusic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 18:11:09 by mmusic            #+#    #+#             */
/*   Updated: 2025/08/03 15:34:10 by mmusic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *monitor_routine(void *arg)
{
    t_philo *philos;
    int     i;
    int     philo_count;
    time_t  last_meal;

    philos = (t_philo *)arg;
    philo_count = philos[0].num_of_philos;
    //(void)philos;
    //printf("hello from monitor thread\n");
    while(1)
    {
        i = 0;
        while(i < philo_count)
        {

            //pthread_mutex_lock(philos[i].m_eating);
            pthread_mutex_lock(philos[i].m_dead);
            last_meal = philos[i].last_meal;
            pthread_mutex_unlock(philos[i].m_dead);
            //printf("philo: %d, difference lastmeal - previous meal: %ld\n", philos[i].id, philos[i].last_meal - last_meal);
            if(current_time() - last_meal > philos[i].time_to_die)
            {
                //printf("philo %d: diff: %ld\n", philos[i].id, current_time() - last_meal);
                print_status(&philos[i], "died");
                pthread_mutex_lock(philos[i].m_dead);
                philos[i].is_dead = true;
                philos[i].data->should_exit = true;
                pthread_mutex_unlock(philos[i].m_dead);
                //pthread_mutex_unlock(philos[i].m_dead);
                //ft_destroy(philos[i].data, philos[i].data->forks);
                //exit(0);
                return NULL;
            }
            if(check_if_all_eaten_max(philos))
                return NULL;
            i++; 
            ft_sleep(1);
        }
    }
    return NULL;
}

int min_times_eaten(t_philo *philos)
{
    int min;
    int i;

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
/* void    eating(t_philo *philo)
{
    // Lock eating mutex first to prevent race conditions
    pthread_mutex_lock(philo->m_eating);
    
    // Lock forks in consistent order (lower index first)
    if (philo->l_fork < philo->r_fork) {
        pthread_mutex_lock(philo->l_fork);
        pthread_mutex_lock(philo->r_fork);
    } else {
        pthread_mutex_lock(philo->r_fork);
        pthread_mutex_lock(philo->l_fork);
    }
    
    print_status(philo, "has taken a fork");
    print_status(philo, "has taken a fork");
    print_status(philo, "is eating");
    
    philo->last_meal = current_time();
    ft_sleep(philo->time_to_eat);
    
    // Unlock in reverse order
    if (philo->l_fork < philo->r_fork) {
        pthread_mutex_unlock(philo->r_fork);
        pthread_mutex_unlock(philo->l_fork);
    } else {
        pthread_mutex_unlock(philo->l_fork);
        pthread_mutex_unlock(philo->r_fork);
    }
    
    philo->num_of_eaten_meals++;
    philo->state = SLEEPING;
     pthread_mutex_unlock(philo->m_eating);
}*/

bool    eating(t_philo *philo)
{
    pthread_mutex_lock(philo->m_dead);
    if (philo->data->should_exit || philo->is_dead) {
        pthread_mutex_unlock(philo->m_dead);
        return false;
    }
	pthread_mutex_unlock(philo->m_dead); 
	if (philo->num_of_philos == 1) {
        pthread_mutex_lock(philo->l_fork);
        print_status(philo, "has taken a fork");
		ft_sleep(philo->time_to_die + 1);
		pthread_mutex_unlock(philo->l_fork);
        return false;
    }
	pthread_mutex_t *first_fork, *second_fork;
    
    if (philo->l_fork < philo->r_fork) {
        first_fork = philo->l_fork;
        second_fork = philo->r_fork;
    } else {
        first_fork = philo->r_fork;
        second_fork = philo->l_fork;
    }
    
    pthread_mutex_lock(first_fork);
    pthread_mutex_lock(second_fork);
	pthread_mutex_lock(philo->m_dead);
    if (philo->data->should_exit || philo->is_dead) {
        pthread_mutex_unlock(philo->m_dead);
        // Unlock forks before returning
        pthread_mutex_unlock(philo->l_fork);
        pthread_mutex_unlock(philo->r_fork);
        return false;
    }
	pthread_mutex_unlock(philo->m_dead);

  /*   pthread_mutex_lock(philo->l_fork);
    print_status(philo, "has taken a fork");
    pthread_mutex_lock(philo->r_fork);
    print_status(philo, "has taken a fork"); */
	print_status(philo, "has taken a fork");
	print_status(philo, "has taken a fork");
    print_status(philo, "is eating");
    pthread_mutex_lock(philo->m_dead);
    philo->last_meal = current_time();
    pthread_mutex_unlock(philo->m_dead);
    // printf("philo %d last meal: %ld\n", philo->id + 1, philo->last_meal - philo->data->start_time);
    // printf("philo %d previous meal: %ld\n", philo->id + 1, philo->previous_meal - philo->data->start_time);
    ft_sleep(philo->time_to_eat);
    pthread_mutex_unlock(philo->l_fork);
    pthread_mutex_unlock(philo->r_fork);
    pthread_mutex_lock(philo->m_eating);
    philo->num_of_eaten_meals++;
    pthread_mutex_unlock(philo->m_eating);
    philo->state = SLEEPING;
    return true;
}
void    sleeping(t_philo *philo)
{
	pthread_mutex_lock(philo->m_dead);
    if (philo->data->should_exit || philo->is_dead) {
        pthread_mutex_unlock(philo->m_dead);
        return;
    }
    pthread_mutex_unlock(philo->m_dead);
    print_status(philo, "is sleeping");
    ft_sleep(philo->time_to_sleep);
    philo->state = THINKING;
}

void    thinking(t_philo *philo)
{
	pthread_mutex_lock(philo->m_dead);
    if (philo->data->should_exit || philo->is_dead) {
        pthread_mutex_unlock(philo->m_dead);
        return;
    }
    pthread_mutex_unlock(philo->m_dead);
    //pthread_mutex_lock(philo->m_printing);
    print_status(philo, "is thinking");
    ft_sleep(1);
    //pthread_mutex_unlock(philo->m_printing);
}

/* bool check_dead(t_philo *philo)
{
    if(current_time() - philo->previous_meal > philo->time_to_die)
    {
        pthread_mutex_lock(philo->m_dead);
        print_status(philo, "died");
        pthread_mutex_unlock(philo->m_dead);
        ft_destroy(philo->data, philo->data->forks);
        return (true);
    }
    return (false);
} */

int check_if_all_eaten_max(t_philo *philos)
{
    int i;
    //int min;
    int max;
    int philo_count;

    i = 0;
    philo_count = philos[0].num_of_philos;
    //min = min_times_eaten(philos);
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


void    *routine(void *arg)
{
    t_philo *philo;
    
    philo = (t_philo *)arg;
    while(philo->is_dead == false && philo->num_of_eaten_meals < philo->max_meals)
    {

		pthread_mutex_lock(philo->m_dead);
        if (philo->data->should_exit || philo->is_dead) {
            pthread_mutex_unlock(philo->m_dead);
            return NULL;
        }
        pthread_mutex_unlock(philo->m_dead);
        if(philo->state == EATING)
        {
            if (!eating(philo))
                return NULL;

            // printf("philo %d previous meal: %ld\n", philo->id + 1,  philo->previous_meal - philo->data->start_time);
            // printf("philo %d last meal: %ld\n", philo->id + 1, philo->last_meal - philo->data->start_time);

        }
        else if(philo->state == SLEEPING)
            sleeping(philo);
        else if(philo->state == THINKING)
        {
            thinking(philo);
            philo->state = EATING;
        }
    }
    /* while(check_if_all_eaten_max(philo->data->philos) == 0 && philo->is_dead == false)
    {
        sleeping(philo);
        thinking(philo);
        ft_sleep(philo->time_to_sleep);
    }
    ft_destroy(philo->data, philo->data->forks);
     */
	return (NULL);
}
