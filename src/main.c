/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmusic <mmusic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 19:43:34 by mmusic            #+#    #+#             */
/*   Updated: 2025/08/04 21:40:39 by mmusic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_philo			philos[200];
	t_data			data;
	pthread_mutex_t	forks[200];
	pthread_t		monitor;

	if (argc < 5 || argc > 6 || check_args(argv) == 0)
		return (printf("incorrect args\n"), 1);
	init_data_and_forks(&data, philos, forks, atol(argv[1]));
	data.start_time = current_time();
	init_p(&data, philos, forks, argv);
	if (pthread_create(&monitor, NULL, monitor_routine, (void *)philos) != 0)
	{
		ft_destroy(&data, forks);
		return (printf("Process terminated due to SIGSEGV Signal. \n"), 1);
	}
	init_threads(&data, philos, forks);
	pthread_join(monitor, NULL);
	ft_destroy(&data, forks);
	return (0);
}
