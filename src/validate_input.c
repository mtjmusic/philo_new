/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmusic <mmusic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 21:19:29 by mmusic            #+#    #+#             */
/*   Updated: 2025/08/04 21:20:24 by mmusic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_nums(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (!ft_isnum(argv[i][j]))
				return (0);
			j++;
		}
		if (j > 10)
			return (0);
		i++;
	}
	return (1);
}

int	check_args(char **argv)
{
	if (!check_nums(argv))
		return (0);
	if (ft_atol(argv[1]) < 1 || ft_atol(argv[1]) > 200)
		return (0);
	if (ft_atol(argv[2]) < 1)
		return (0);
	if (ft_atol(argv[3]) < 1)
		return (0);
	if (ft_atol(argv[4]) < 1)
		return (0);
	if (argv[5] && ft_atol(argv[5]) < 1)
		return (0);
	return (1);
}

int	ft_isnum(char c)
{
	return (c >= '0' && c <= '9');
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (*str)
	{
		i++;
		str++;
	}
	return (i);
}

long	ft_atol(char *str)
{
	long	out;

	out = 0;
	while (*str)
	{
		out = 10 * out + (*str) % '0';
		str++;
	}
	return (out);
}
