/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmusic <mmusic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 19:43:34 by mmusic            #+#    #+#             */
/*   Updated: 2025/02/26 17:02:01 by mmusic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int check_nums(char **argv)
{
    int i;
    int j;

    i = 1;
    while(argv[i])
    {
        j = 0;
        while(argv[i][j])
        {
            if(!ft_isnum(argv[i][j]))
                return (0);
            j++;
        }
        if (j > 10)
            return (0);
        i++;
    }
    return (1);
}

int check_args(char **argv)
{
    if(!check_nums(argv))
        return (0);
    if(ft_atol(argv[1]) < 1 || ft_atol(argv[1]) > 200)
        return (0);
    if(ft_atol(argv[2]) < 1)
        return (0);
    if(ft_atol(argv[3]) < 1)
        return (0);
    if(ft_atol(argv[4]) < 1)
        return (0);
    if(argv[5] && ft_atol(argv[5]) < 1)
        return (0);
    return (1);
}


int main(int argc, char **argv)
{
    t_philo         philos[200];
    t_data          data;    
    pthread_mutex_t forks[200];
    pthread_t       monitor;
    
    if(argc < 5 || argc > 6 || check_args(argv) == 0)
        return(printf("incorrect args\n"),1);
    init_data(&data, philos, forks);
    init_forks(forks, ft_atol(argv[1]));
    data.start_time = current_time();
    init_p(&data, philos, forks, argv);
    if(pthread_create(&monitor, NULL, monitor_routine, (void *)philos) != 0)
        ft_destroy(&data, forks);
    init_threads(&data, philos, forks);
    if(pthread_join(monitor, NULL) != 0)
		ft_destroy(&data, forks);
	ft_destroy(&data, forks);
	return (0);
}
