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

/* void    print_status(t_philo *philo, char *status)
{
    pthread_mutex_lock(philo->m_printing);
    printf("%ld %d %s\n", current_time() - philo->data->start_time, philo->id + 1, status);
    pthread_mutex_unlock(philo->m_printing);
} */

void ft_destroy(t_data *data, pthread_mutex_t *forks)
{
    int i;

    i = 0;
    while(i < data->num_philos)
    {
        pthread_mutex_destroy(&forks[i]);
        //pthread_mutex_destroy(data->philos[i].m_eating);
        //free(data->philos[i].m_eating);
        i++;
    }
    exit(0);
}