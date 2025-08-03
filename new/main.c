
#include "philo.h"

void init_data(t_data *data, char **argv)
{
	data->num_philos = ft_atol(argv[1]);
	data->time_to_die = ft_atol(argv[2]);
	data->time_to_eat = ft_atol(argv[3]);
	data->time_to_sleep = ft_atol(argv[4]);
	if(argv[5])
		data->num_times_each_philo_must_eat = ft_atol(argv[5]);
	else
		data->num_times_each_philo_must_eat = -1;
	data->start_time = 0;

}
void	init_forks(pthread_mutex_t *forks, int num_philos)
{
	int i;

	i = 0;
	while(i < num_philos)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
}

void init_state(int i, t_state *state, int num_philos)
{
	bool is_odd;

	is_odd = num_philos % 2;
	printf("i: %d\n", i);
	if(is_odd)
	{
		if(i == num_philos - 1)
			*state = THINKING;
		else if(i % 2 == 0)
			*state = SLEEPING;
		else
			*state = EATING;
	}
	else
	{
		if(i % 2 == 0)
			*state = EATING;
		else
			*state = THINKING;
	}
}

void init_philos(t_philo *philos, t_data *data, pthread_mutex_t *forks)
{
	int i;

	i = 0;
	while (i < data->num_philos)
	{
		philos[i].id = i + 1;
		philos[i].last_meal_time = 0;
		philos[i].meals_eaten = 0;
		philos[i].left_fork = &forks[i];
		if (i == data->num_philos - 1)
			philos[i].right_fork = &forks[0];
		else
			philos[i].right_fork = &forks[i + 1];
		philos[i].is_dead = 0;
		init_state(i, &philos[i].state, data->num_philos);
		
		i++;
	}
}

void *routine(void *arg)
{
	t_philo *philo = (t_philo *)arg;
	printf("Philosopher %d thread started\n", philo->id);
	// Simulate philosopher actions here
	/* t_philo *philo = (t_philo *)arg;

	while (1)
	{
		if (*philo->is_dead)
			break;
		// Simulate philosopher actions here
	} */
	return (NULL);
}

void init_threads(t_philo *philos, t_data *data)
{
	int i;

	i = 0;
	while(i < data->num_philos)
	{
		if(pthread_create(&philos[i].thread, NULL, &routine, &philos[i]) != 0)
		{
			perror("Failed to create thread");
			exit(EXIT_FAILURE);
		}
		i++;
	}
	i = 0;
	while(i < data->num_philos)
	{
		if(pthread_join(philos[i].thread, NULL) != 0)
		{
			perror("Failed to join thread");
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

void *monitor_routine(void *arg)
{
	arg = NULL; // Prevent unused parameter warning
	printf("Monitor thread started\n");
	return (NULL);
}




int main(int argc, char **argv)
{

	t_data data;
	pthread_mutex_t forks[200];
	t_philo philos[200];
	pthread_t monitor;

    if ((argc != 5 && argc != 6) || !check_args(argv))
    {
        printf("Usage: ./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]\n");
        return (1);
    }
	init_data(&data, argv);
	init_forks(forks, data.num_philos);
	init_philos(philos, &data, forks);
	int i = 0;
	while(i < data.num_philos)
	{
		printf("Philosopher %d initialized with state %d\n", philos[i].id, philos[i].state);
		i++;
	}
	if(pthread_create(&monitor, NULL, &monitor_routine, NULL) != 0)
	{
		perror("Failed to create monitor thread");
		exit(EXIT_FAILURE);
	}
	init_threads(philos, &data);

	return (0);
}