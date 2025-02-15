/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oayyoub <oayyoub@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 08:29:59 by oayyoub           #+#    #+#             */
/*   Updated: 2025/02/14 09:27:44 by oayyoub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	ft_atoll(const char *str)
{
	long long	nbr;
	int			sign;

	nbr = 0;
	sign = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		nbr = nbr * 10 + *str - '0';
		str++;
	}
	return (nbr * sign);
}

size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	print_error(char *str)
{
	if (!str)
		return ;
	write (2, str, ft_strlen(str));
	exit(1);
}

int	check_input(char **av)
{
	int	i;
	int	j;

	i = 0;
	while (av[i])
	{
		j = 0;
		if (av[i][j] == '+' && av[i][j + 1])
			j++;
		while (av[i][j] >= '0' && av[i][j] <= '9')
			j++;
		if (av[i][j])
			return (1);
		i++;
	}
	return (0);
}

void	_input(char **av, t_data *data)
{
	data->nbr_philo = ft_atoll(av[0]);
	data->time_to_die = ft_atoll(av[1]);
	data->time_to_eat = ft_atoll(av[2]);
	data->time_to_sleep = ft_atoll(av[3]);
	if (av[4])
	{
		data->eat_limit = ft_atoll(av[4]);
		if (data->eat_limit <= 0)
			print_error("Error: Invalid input\n");
	}
	else
		data->eat_limit = -1;
	if (data->nbr_philo <= 0 || data->time_to_die <= 0
		|| data->time_to_eat <= 0 || data->time_to_sleep <= 0)
		print_error("Error: Invalid input\n");
}
